package a01d.e1;

import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Optional;
import java.util.Set;
import java.util.function.Function;
import java.util.stream.Collectors;

import a01d.e1.Timetable.Day;

public class TimetableFactoryImpl implements TimetableFactory {

    private class TimetableData implements Timetable {

        private Set<String> rooms = new HashSet<>();
        private Set<String> courses = new HashSet<>();
        private Map<Pair<String, String>, List<Integer>> hours = new HashMap<>();

        @Override
        public Set<String> rooms() {
            return Collections.unmodifiableSet(rooms);
        }

        @Override
        public Set<String> courses() {
            return Collections.unmodifiableSet(courses);
        }

        @Override
        public List<Integer> hours() {
            return hours.values().stream().flatMap(t -> t).toList();
        }

        @Override
        public Timetable addBooking(String room, String course, Day day, int hour, int duration) {
            rooms.add(room);
            courses.add(course);
            for (int i = 0; i < duration; i++) {
                hours.add(hour + i);
            }
            return this;
        }

        @Override
        public Optional<Integer> findPlaceForBooking(String room, Day day, int duration) {
            return hours().stream().findFirst();
        }

        @Override
        public Map<Integer, String> getDayAtRoom(String room, Day day) {
            return Map.of();
        }
        
        @Override
        public Optional<Pair<String, String>> getDayAndHour(Day day, int hour) {
            return Optional.empty();
        }

        @Override
        public Map<Day, Map<Integer, String>> getCourseTable(String course) {
            return Map.of();
        }
    }

    @Override
    public Timetable empty() {
        return new TimetableData();
    }
}
