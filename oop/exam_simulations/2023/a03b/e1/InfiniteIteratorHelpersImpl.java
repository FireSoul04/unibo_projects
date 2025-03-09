package a03b.e1;

import java.util.Iterator;
import java.util.List;
import java.util.stream.Stream;

public class InfiniteIteratorHelpersImpl implements InfiniteIteratorsHelpers {

    @Override
    public <X> InfiniteIterator<X> of(X x) {
        return () -> x;
    }

    private static class InfiniteIteratorCyclic<X> implements InfiniteIterator<X> {
        private int index = 0;
        private final List<X> elem;

        public InfiniteIteratorCyclic(List<X> elem) {
            this.elem = elem;
        }

        @Override
        public X nextElement() {
            final var ret = elem.get(index);
            index = (index + 1) % elem.size();
            return ret;
        }
    }

    @Override
    public <X> InfiniteIterator<X> cyclic(List<X> l) {
        return new InfiniteIteratorCyclic<>(l);
    }

    private static class InfiniteIteratorIncrementing implements InfiniteIterator<Integer> {
        private final Stream<Integer> elem;
        private final Iterator<Integer> it;

        public InfiniteIteratorIncrementing(int start, int increment) {
            elem = Stream.iterate(start, i -> i + increment);
            it = elem.iterator();
        } 

        @Override
        public Integer nextElement() {
            return it.next();
        }
    }

    @Override
    public InfiniteIterator<Integer> incrementing(int start, int increment) {
        return new InfiniteIteratorIncrementing(start, increment);
    }
    
    private static class InfiniteIteratorAlternating<X> implements InfiniteIterator<X> {
        private int index = 0;
        private final List<InfiniteIterator<X>> it; 

        public InfiniteIteratorAlternating(InfiniteIterator<X> i, InfiniteIterator<X> j) {
            it = List.of(i, j);
        }

        @Override
        public X nextElement() {
            final var ret = it.get(index).nextElement();
            index = (index + 1) % 2;
            return ret;
        }
    }

    @Override
    public <X> InfiniteIterator<X> alternating(InfiniteIterator<X> i, InfiniteIterator<X> j) {
        return new InfiniteIteratorAlternating<>(i, j); 
    }

    @Override
    public <X> InfiniteIterator<List<X>> window(InfiniteIterator<X> i, int n) {
        return null;
    }

}
