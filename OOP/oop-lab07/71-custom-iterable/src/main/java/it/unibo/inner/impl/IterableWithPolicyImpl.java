package it.unibo.inner.impl;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Iterator;

import it.unibo.inner.api.IterableWithPolicy;
import it.unibo.inner.api.Predicate;

public class IterableWithPolicyImpl<T> implements IterableWithPolicy<T> {

    private final IteratorWithPolicy iterator;
    private Predicate<T> predicate;
    
    private class IteratorWithPolicy implements Iterator<T> {

        private final ArrayList<T> arrayToIterate;
        private int current;

        public IteratorWithPolicy(final T[] array) {
            this.arrayToIterate = new ArrayList<T>(Arrays.asList(array));
            this.current = 0;
        }

        @Override
        public T next() {
            return this.arrayToIterate.get(this.current++);
        }

        @Override
        public boolean hasNext() {
            while (
                this.current < this.arrayToIterate.size()
                && !predicate.test(this.arrayToIterate.get(this.current))
            ) {
                this.current++;
            }

            return this.current < this.arrayToIterate.size() 
                && predicate.test(this.arrayToIterate.get(this.current));
        }

        @Override
        public String toString() {
            return arrayToIterate.toString();
        }
    };

    public IterableWithPolicyImpl(final T[] array) {
        this(array, new Predicate<>() {
            public boolean test(final T elem) {
                return true;
            }
        });
    }

    public IterableWithPolicyImpl(final T[] array, final Predicate<T> predicate) {
        this.iterator = new IteratorWithPolicy(array);
        this.predicate = predicate;
    }

    @Override
    public void setIterationPolicy(final Predicate<T> filter) {
        this.predicate = filter;
    }

    @Override
    public Iterator<T> iterator() {
        return this.iterator;
    }
    
    @Override
    public String toString() {
        return this.iterator.arrayToIterate.toString();
    }
}
