package it.unibo.nestedenum;

import java.util.Comparator;
import java.util.Locale;
import java.util.Objects;

/**
 * Implementation of {@link MonthSorter}.
 */
public final class MonthSorterNested implements MonthSorter {

    enum Month {
        JANUARY(31),
        FEBRUARY(28),
        MARCH(31),
        APRIL(30),
        MAY(31),
        JUNE(30),
        JULY(31),
        AUGUST(31),
        SEPTEMBER(30),
        OCTOBER(31),
        NOVEMBER(30),
        DECEMBER(31);

        private final int days;

        private Month(final int days) {
            this.days = days;
        }

        public int getDays() {
            return this.days;
        }

        public static Month fromString(final String name) throws IllegalArgumentException {
            final String upperCaseName = Objects.requireNonNull(name.toUpperCase());
            Month returnValue = null;
            int monthsThatContainsName = 0;
            for (final Month month : Month.values()) {
                if (month.name().contains(upperCaseName)) {
                    returnValue = month;
                    monthsThatContainsName++;
                }
            }
            if (returnValue == null) {
                throw new IllegalArgumentException("Invalid month name");
            } else if (monthsThatContainsName != 1) {
                throw new IllegalArgumentException("Ambiguous month name");
            } else {
                return returnValue;
            }
        }

        public static int compare(final Month m1, final Month m2) {
            return Integer.compare(m1.ordinal(), m2.ordinal());
        }

        public static int compareDays(final Month m1, final Month m2) {
            return Integer.compare(m1.getDays(), m2.getDays());
        }
    };

    @Override
    public Comparator<String> sortByDays() {
        return new Comparator<String>() {
            @Override
            public int compare(final String month1, final String month2) {
                return Month.compareDays(
                    Month.fromString(month1), 
                    Month.fromString(month2)
                );
            }
        };
    }

    @Override
    public Comparator<String> sortByOrder() {
        return new Comparator<String>() {
            @Override
            public int compare(final String month1, final String month2) {
                return Month.compare(
                    Month.fromString(month1), 
                    Month.fromString(month2)
                ); 
            }
        };
    }
}
