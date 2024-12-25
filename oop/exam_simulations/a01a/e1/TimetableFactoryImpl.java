package a01a.e1;

import java.util.*;
import java.util.function.BiFunction;
import java.util.stream.Collectors;

public class TimetableFactoryImpl implements TimetableFactory {

    @Override
    public Timetable empty() {
        return new TimetableImpl();
    }

    @Override
    public Timetable single(final String activity, final String day) {
        return this.empty().addHour(activity, day);
    }

    @Override
    public Timetable join(final Timetable table1, final Timetable table2) {
        final Timetable joinedTimetable = this.empty();
        this.add(joinedTimetable, table1);
        this.add(joinedTimetable, table2);
        return joinedTimetable;
    }

    private void add(final Timetable tableToJoin, final Timetable table) {
        for (final String activity : table.activities()) {
            for (final String day : table.days()) {
                final int hours = table.getSingleData(activity, day);
                for (int i = 0; i < hours; i++) {
                    tableToJoin.addHour(activity, day);
                }
            }
        }
    }

    @Override
    public Timetable cut(final Timetable table, final BiFunction<String, String, Integer> bounds) {
        final Timetable cutTimetable = this.empty();
        for (final String activity : table.activities()) {
            for (final String day : table.days()) {
                final int hours = table.getSingleData(activity, day);
                if (hours <= bounds.apply(activity, day)) {
                    for (int i = 0; i < hours; i++) {
                        cutTimetable.addHour(activity, day);
                    }
                }
            }
        }
        return cutTimetable;
    }

    private class TimetableImpl implements Timetable {

        private final Map<TimetableCell, Integer> hours = new HashMap<>();

        @Override
        public Timetable addHour(final String activity, final String day) {
            final TimetableCell cell = new TimetableCell(activity, day);
            int hours = 0;
            if (this.hours.containsKey(cell)) {
                hours = this.hours.get(cell);
            }
            this.hours.put(cell, hours + 1);
            return this;
        }

        @Override
        public Set<String> activities() {
            return Collections.unmodifiableSet(this.hours.keySet()
                .stream()    
                .map(t -> t.getActivity())
                .collect(Collectors.toSet())
            );
        }

        @Override
        public Set<String> days() {
            return Collections.unmodifiableSet(this.hours.keySet()
                .stream()
                .map(t -> t.getDay())
                .collect(Collectors.toSet())
            );
        }

        @Override
        public int getSingleData(final String activity, final String day) {
            final TimetableCell cell = new TimetableCell(activity, day);
            if (this.hours.containsKey(cell)) {
                return this.hours.get(cell);
            }
            return 0;
        }

        @Override
        public int sums(final Set<String> activities, final Set<String> days) {
            int count = 0;
            for (final String activity : activities) {
                for (final String day : days) {
                    count = count + this.getSingleData(activity, day);
                }
            }
            return count;
        }
    }
        
    public class TimetableCell {

        private final Pair<String, String> cell;

        public TimetableCell(final String activity, final String day) {
            this.cell = new Pair<>(activity, day);
        }

        public String getActivity() {
            return this.cell.get1();
        }

        public String getDay() {
            return this.cell.get2();
        }

        @Override
        public int hashCode() {
            return this.cell.hashCode();
        }

        @Override
        public boolean equals(final Object o) {
            return this == o
                || this.cell.equals(((TimetableCell) o).cell);
        }

        @Override
        public String toString() {
            return this.cell.toString();
        }
    }
}
