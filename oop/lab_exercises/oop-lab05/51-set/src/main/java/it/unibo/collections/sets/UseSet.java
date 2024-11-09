package it.unibo.collections.sets;

import java.util.Collection;
import java.util.TreeSet;
import java.util.Set;

/**
 * Example class using {@link java.util.Set}.
 *
 */
public final class UseSet {

    private static final int ELEMS = 20;

    private UseSet() {
    }

    /**
     * @param args
     *            ignored
     */
    public static void main(final String[] args) {
        /*
         * Considering the content of "UseCollection, write a program which, in
         * order:
         *
         * 1) Builds a TreeSet containing Strings
         */
        final Set<String> stringSet = new TreeSet<>();
        /*
         * 2) Populates such Collection with all the Strings representing numbers ranging from "1" to
         * "20" (both included)
         */
        for (int i = 1; i <= 20; i++) {
            stringSet.add(Integer.toString(i));
        }
        /*
         * 3) Prints its content
         */
        System.out.println(stringSet);
        /*
         * 4) Removes all those strings whose represented number is divisible by three.
         * Note: the method removeIf(Predicate) is not allowed.
         */
        for (final var myIterator = stringSet.iterator(); myIterator.hasNext();) {
            int num = Integer.valueOf(myIterator.next());
            if (num % 3 == 0) {
                myIterator.remove();
            }
        }
        /*
         * 5) Prints the content of the Set using a for-each construct
         */
        for (final String num : stringSet) {
            System.out.println(num);
        }
        /*
         * 6) Verifies whether all the numbers left in the set are even
         */
        boolean areAllEven = true;
        for (final String num : stringSet) {
            if (Integer.valueOf(num) % 2 != 0) {
                areAllEven = false;
            }
        }
        System.out.println("All numbers are " + (areAllEven ? "" : "not") + " even");
    }
}
