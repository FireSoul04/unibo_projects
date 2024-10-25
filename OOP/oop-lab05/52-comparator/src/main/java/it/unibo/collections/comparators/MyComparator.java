package it.unibo.collections.comparators;

import java.util.Comparator;

public class MyComparator implements Comparator<String> { 

    @Override
    public int compare(String o1, String o2) {
        final double n1 = Double.valueOf(o1);
        final double n2 = Double.valueOf(o2);
        return Double.compare(n1, n2); 
    }
}
