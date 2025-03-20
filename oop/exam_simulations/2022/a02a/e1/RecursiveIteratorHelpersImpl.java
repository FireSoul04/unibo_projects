package a02a.e1;

import java.util.LinkedList;
import java.util.List;
import java.util.stream.Stream;

public class RecursiveIteratorHelpersImpl implements RecursiveIteratorHelpers {

    private static class RecursiveIteratorImpl<X> implements RecursiveIterator<X> {
        private final List<X> input;

        public RecursiveIteratorImpl(final List<X> input) {
            this.input = new LinkedList<>(input);
        }

        @Override
        public X getElement() {
            return input.isEmpty() ? null : input.getFirst();
        }

        @Override
        public RecursiveIterator<X> next() {
            if (!input.isEmpty()) {
                input.removeFirst();
            }
            return input.isEmpty() ? null : new RecursiveIteratorImpl<>(input);
        }
    }

    private <X> List<X> convertToList(RecursiveIterator<X> it) {
        final List<X> ret = new LinkedList<>();
        while (it != null) {
            ret.add(it.getElement());
            it = it.next();
        }
        return ret;
    }

    @Override
    public <X> RecursiveIterator<X> fromList(List<X> list) {
        return list.isEmpty() ? null : new RecursiveIteratorImpl<>(list);
    }

    @Override
    public <X> List<X> toList(RecursiveIterator<X> input, int max) {
        return convertToList(input).stream().limit(max).toList();
    }

    @Override
    public <X, Y> RecursiveIterator<Pair<X, Y>> zip(RecursiveIterator<X> first, RecursiveIterator<Y> second) {
        final List<Pair<X, Y>> solution = new LinkedList<>();
        while (first != null && second != null) {
            solution.add(new Pair<X,Y>(first.getElement(), second.getElement()));
            first = first.next();
            second = second.next();
        }
        return fromList(solution);
    }

    @Override
    public <X> RecursiveIterator<Pair<X, Integer>> zipWithIndex(RecursiveIterator<X> iterator) {
        final List<X> ret = convertToList(iterator);
        return zip(fromList(ret), fromList(Stream.iterate(0, i -> i < ret.size(), i -> i + 1).toList()));
    }

    @Override
    public <X> RecursiveIterator<X> alternate(RecursiveIterator<X> first, RecursiveIterator<X> second) {
        final List<X> firstList = convertToList(first);
        final List<X> secondList = convertToList(second);
        final List<X> solution = new LinkedList<>();
        int indexFirst = 0;
        int indexSecond = 0;
        for (int i = 0; i < firstList.size(); i++) {
            if (i % 2 == 0) {
                solution.add(firstList.get(indexFirst));
                indexFirst++;
            } else {
                solution.add(secondList.get(indexSecond));
                indexSecond++;
            }
        }
        for (int i = indexFirst; i < firstList.size(); i++) {
            solution.add(firstList.get(i));
        }
        for (int i = indexSecond; i < secondList.size(); i++) {
            solution.add(secondList.get(i));
        }
        return fromList(solution);
    }

}
