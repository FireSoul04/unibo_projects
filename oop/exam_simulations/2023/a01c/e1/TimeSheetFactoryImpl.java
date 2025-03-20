package a01c.e1;

import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.function.BiFunction;
import java.util.function.BiPredicate;
import java.util.stream.Collectors;

public class TimeSheetFactoryImpl implements TimeSheetFactory {

    private static record TimeSheetData(Set<String> activities, Set<String> days, BiFunction<String, String, Integer> data, BiPredicate<Set<String>, Set<String>> valid) implements TimeSheet {
        @Override
        public int getSingleData(String activity, String day) {
            return data.apply(activity, day);
        }

        @Override
        public boolean isValid() {
            return valid.test(activities, days);
        }
    }

    @Override
    public TimeSheet ofRawData(List<Pair<String, String>> data) {
        Set<String> activities = data.stream().map(t -> t.get1()).collect(Collectors.toSet());
        Set<String> days = data.stream().map(t -> t.get2()).collect(Collectors.toSet());
        return new TimeSheetData(
            activities,
            days,
            (a, d) -> (int) data.stream().filter(t -> t.get1().equals(a) && t.get2().equals(d)).count(),
            (a, d) -> true
        );
    }

    @Override
    public TimeSheet withBoundsPerActivity(List<Pair<String, String>> data, Map<String, Integer> boundsOnActivities) {
        Set<String> activities = data.stream().map(t -> t.get1()).collect(Collectors.toSet());
        Set<String> days = data.stream().map(t -> t.get2()).collect(Collectors.toSet());
        return new TimeSheetData(
            activities,
            days,
            (a, d) -> (int) data.stream().filter(t -> t.get1().equals(a) && t.get2().equals(d)).count(),
            (a, d) -> boundsOnActivities.entrySet()
                .stream()
                .allMatch(t -> getHoursPerActivity(data, t.getKey()) <= t.getValue())
        );
    }

    @Override
    public TimeSheet withBoundsPerDay(List<Pair<String, String>> data, Map<String, Integer> boundsOnDays) {
        Set<String> activities = data.stream().map(t -> t.get1()).collect(Collectors.toSet());
        Set<String> days = data.stream().map(t -> t.get2()).collect(Collectors.toSet());
        return new TimeSheetData(
            activities,
            days,
            (a, d) -> (int) data.stream().filter(t -> t.get1().equals(a) && t.get2().equals(d)).count(),
            (a, d) -> boundsOnDays.entrySet()
                .stream()
                .allMatch(t -> getHoursPerDay(data, t.getKey()) <= t.getValue())
        );
    }

    @Override
    public TimeSheet withBounds(
        List<Pair<String, String>> data,
        Map<String, Integer> boundsOnActivities,
        Map<String, Integer> boundsOnDays
    ) {
        Set<String> activities = data.stream().map(t -> t.get1()).collect(Collectors.toSet());
        Set<String> days = data.stream().map(t -> t.get2()).collect(Collectors.toSet());
        return new TimeSheetData(
            activities,
            days,
            (a, d) -> (int) data.stream().filter(t -> t.get1().equals(a) && t.get2().equals(d)).count(),
            (a, d) -> boundsOnDays.entrySet()
                .stream()
                .allMatch(t -> 
                    getHoursPerActivity(data, t.getKey()) <= t.getValue() &&
                    getHoursPerDay(data, t.getKey()) <= t.getValue()
                )
        );
    }

    private int getHoursPerActivity(List<Pair<String, String>> data, String activity) {
        return (int) data.stream().filter(i -> i.get1().equals(activity)).count();
    }

    private int getHoursPerDay(List<Pair<String, String>> data, String day) {
        return (int) data.stream().filter(i -> i.get2().equals(day)).count();
    }

}
