package it.unibo.collections.comparators;

import java.util.Set;
import java.util.TreeSet;
import java.util.Comparator;
import it.unibo.collections.comparators.MyComparator;

/**
 * 
 */
public final class UseSetWithOrder {

    private UseSetWithOrder() {
    }

    /**
     * @param s
     *            ignored
     */
    public static void main(final String[] s) {

        final int MAX_NUMS = 100;
        /*
         * Write a program which:
         * 
         * 1) Creates a new ORDERED TreeSet of Strings.
         * To order the set, define a new Comparator in a separate class.
         * The comparator must convert the strings to double, then compare the doubles to find the biggest.
         * The comparator does not need to deal with the case of Strings which are not parseable as doubles.
         */
        final Comparator myComparator = new MyComparator();
        final Set<String> stringSet = new TreeSet<>(myComparator); 
        /*
         * 2) Inserts in the set a hundred strings containing randomly generated numbers
         * (use Math.random(), and convert to String appropriately)
         */
        for (int i = 0; i < MAX_NUMS; i++) {
            final double num = Math.random();
            stringSet.add(Double.toString(num));
        }
        /*
         * 3) Prints the set, which must be ordered
         */
        for (final String num : stringSet) {
            System.out.println(num);
        }
    }
}
