package a01b.e1;

import java.util.List;
import java.util.Map;
import java.util.function.BiFunction;
import java.util.function.Function;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class TimeSheetFactoryImpl implements TimeSheetFactory {

    private static record TimeSheetData(List<String> activities, List<String> days, BiFunction<String, String, Integer> data) implements TimeSheet {
        @Override
        public int getSingleData(String activity, String day) {
            return activities.contains(activity) && days.contains(day) ? data.apply(activity, day) : 0;
        }

        @Override
        public Map<String, Integer> sumsPerActivity() {
            return activities.stream()
                .collect(
                    Collectors.toMap(
                        Function.identity(), 
                        (a -> days.stream().mapToInt(d -> data.apply(a, d)).sum())
                    )
                );
        }

        @Override
        public Map<String, Integer> sumsPerDay() {
            return days.stream()
                .collect(
                    Collectors.toMap(
                        Function.identity(), 
                        (d -> activities.stream().mapToInt(a -> data.apply(a, d)).sum())
                    )
                );
        }
    }

    @Override
    public TimeSheet flat(int numActivities, int numNames, int hours) {
        return new TimeSheetData(
            Stream.iterate(1, t -> t + 1).limit(numActivities).map(t -> "act" + t).toList(),
            Stream.iterate(1, t -> t + 1).limit(numNames).map(t -> "day" + t).toList(),
            (a, d) -> hours
        );
    }

    @Override
    public TimeSheet ofListsOfLists(List<String> activities, List<String> days, List<List<Integer>> data) {
        return new TimeSheetData(activities, days, (a, d) -> data
            .get(activities.stream().collect(Collectors.toMap(Function.identity(), t -> activities.indexOf(t))).get(a))
            .get(days.stream().collect(Collectors.toMap(Function.identity(), t -> days.indexOf(t))).get(d))
        );
    }

    @Override
    public TimeSheet ofRawData(int numActivities, int numDays, List<Pair<Integer, Integer>> data) {
        List<String> activities = Stream.iterate(1, t -> t + 1).limit(numActivities).map(t -> "act" + t).toList();
        List<String> days = Stream.iterate(1, t -> t + 1).limit(numDays).map(t -> "day" + t).toList();
        return new TimeSheetData(
            activities,
            days,
            (a, d) -> flat(
                numActivities,
                numDays,
                (int) data.stream()
                    .filter(t -> t.equals(new Pair<>(activities.indexOf(a), days.indexOf(d))))
                    .count()
            ).getSingleData(a, d)
        );
    }

    @Override
    public TimeSheet ofPartialMap(List<String> activities, List<String> days, Map<Pair<String, String>, Integer> data) {
        return new TimeSheetData(
            activities,
            days,
            (a, d) -> data.getOrDefault(new Pair<>(a, d), 0)
        );
    }

}
