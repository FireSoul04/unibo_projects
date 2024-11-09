package it.unibo.collections;

import java.util.*;
import java.util.concurrent.TimeUnit;

/**
 * Example class using {@link List} and {@link Map}.
 *
 */
public final class UseListsAndMaps {

    private static final int MAX_INSERT = 100_000;
    private static final int MAX_READ = 1000;
    
    private static final int START = 1000;
    private static final int END = 2000;

    private UseListsAndMaps() {
    }

    private static void calculateTimeInsert(final List<Integer> list, final String listType) {
        long time = System.nanoTime();
 
        for (int i = 0; i < MAX_INSERT; i++) {
            list.addFirst(i);
        }

        time = System.nanoTime() - time;
        final var millis = TimeUnit.NANOSECONDS.toMillis(time);
        System.out.println(
            "Inserted "
                + list.size()
                + " ints in " 
                + listType
                + " took "
                + time 
                + "ns ("
                + millis 
                + "ms)"
        );
    }

    private static void calculateTimeRead(final List<Integer> list, final String listType) {
        long time = System.nanoTime();
 
        for (int i = 0; i < MAX_READ; i++) {
            list.get(list.size() / 2);
        }

        time = System.nanoTime() - time;
        final var millis = TimeUnit.NANOSECONDS.toMillis(time);
        System.out.println(
            "Read "
                + list.size()
                + " ints in " 
                + listType
                + " took "
                + time 
                + "ns ("
                + millis 
                + "ms)"
        );
    }

    /**
     * @param s
     *            unused
     */
    public static void main(final String... s) {
        /*
         * 1) Create a new ArrayList<Integer>, and populate it with the numbers
         * from 1000 (included) to 2000 (excluded).
         */
        final List<Integer> arrayList = new ArrayList<>();
        for (int i = START; i < END; i++) {
            arrayList.addFirst(i);
        }
        /*
         * 2) Create a new LinkedList<Integer> and, in a single line of code
         * without using any looping construct (for, while), populate it with
         * the same contents of the list of point 1.
         */
        final List<Integer> linkedList = new LinkedList<>(List.copyOf(arrayList));
        /*
         * 3) Using "set" and "get" and "size" methods, swap the first and last
         * element of the first list. You can not use any "magic number".
         * (Suggestion: use a temporary variable)
         */
        final int temp = arrayList.getFirst();
        arrayList.set(0, arrayList.getLast());
        arrayList.set(arrayList.size() - 1, temp);
        /*
         * 4) Using a single for-each, print the contents of the arraylist.
         */
        for (final int n : arrayList) {
            System.out.println(n);
        }
        /*
         * 5) Measure the performance of inserting new elements in the head of
         * the collection: measure the time required to add 100.000 elements as
         * first element of the collection for both ArrayList and LinkedList,
         * using the previous lists. In order to measure times, use as example
         * TestPerformance.java.
         */
        calculateTimeInsert(arrayList, "arrayList");
        calculateTimeInsert(linkedList, "linkedList");
        /*
         * 6) Measure the performance of reading 1000 times an element whose
         * position is in the middle of the collection for both ArrayList and
         * LinkedList, using the collections of point 5. In order to measure
         * times, use as example TestPerformance.java.
         */
        calculateTimeRead(arrayList, "arrayList");
        calculateTimeRead(linkedList, "linkedList");
        /*
         * 7) Build a new Map that associates to each continent's name its
         * population:
         *
         * Africa -> 1,110,635,000
         *
         * Americas -> 972,005,000
         *
         * Antarctica -> 0
         *
         * Asia -> 4,298,723,000
         *
         * Europe -> 742,452,000
         *
         * Oceania -> 38,304,000
         */
        final Map<String, Long> populationMap = new HashMap<>();
        populationMap.put("Africa", 1_110_635_000L);
        populationMap.put("Americas", 972_005_000L);
        populationMap.put("Antartica", 0L);
        populationMap.put("Asia", 4_298_723_000L);
        populationMap.put("Europe", 742_452_000L);
        populationMap.put("Oceania", 38_304_000L);
        /*
         * 8) Compute the population of the world
         */
        long worldPopulation = 0; 
        for (final long continentPopulation : populationMap.values()) {
            worldPopulation = worldPopulation + continentPopulation;
        }
        System.out.println("World population is: " + worldPopulation);
    }
}
