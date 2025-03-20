package a01d.e1;

import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Optional;
import java.util.Set;
import java.util.function.Function;
import java.util.stream.Collectors;

import a01d.e1.Timetable.Day;

public class TimetableFactoryImpl implements TimetableFactory {

    private static record Booking(String room, String course, Day day, int hour) {
    }

    private static record TimetableData(Set<Booking> bookings) implements Timetable {

        @Override
        public Set<String> rooms() {
            return bookings.stream().map(Booking::room).collect(Collectors.toSet());
        }

        @Override
        public Set<String> courses() {
            return bookings.stream().map(Booking::course).collect(Collectors.toSet());
        }

        @Override
        public List<Integer> hours() {
            return bookings.stream().map(Booking::hour).distinct().sorted().toList();
        }

        @Override
        public Timetable addBooking(String room, String course, Day day, int hour, int duration) {
            for (int i = 0; i < duration; i++) {
                bookings.add(new Booking(room, course, day, hour + i));
            }
            return this;
        }

        @Override
        public Optional<Integer> findPlaceForBooking(String room, Day day, int duration) {
            return hours().stream()
                .filter(a -> bookings.stream()
                    .filter(t -> t.room().equals(room))
                    .filter(t -> t.day().equals(day))
                    .map(t -> t.hour())
                    .count() == duration
                )
                .sorted()
                .findFirst();
        }

        @Override
        public Map<Integer, String> getDayAtRoom(String room, Day day) {
            return bookings.stream()
                .filter(t -> t.room().equals(room))
                .filter(t -> t.day().equals(day))
                .collect(Collectors.toMap(Booking::hour, Booking::course));
        }
        
        @Override
        public Optional<Pair<String, String>> getDayAndHour(Day day, int hour) {
            return bookings.stream()
                .filter(t -> t.day().equals(day))
                .filter(t -> t.hour() == hour)
                .map(t -> new Pair<>(t.course(), t.room()))
                .findFirst();
        }

        @Override
        public Map<Day, Map<Integer, String>> getCourseTable(String course) {
            return bookings.stream()
                .filter(t -> t.course().equals(course))
                .map(t -> t.day())
                .distinct()
                .collect(Collectors.toMap(Function.identity(), t -> bookings.stream()
                    .filter(a -> a.day().equals(t))
                    .filter(a -> a.course().equals(course))
                    .collect(Collectors.toMap(Booking::hour, Booking::room))
                ));
        }
    }

    @Override
    public Timetable empty() {
        return new TimetableData(new HashSet<>());
    }
}
