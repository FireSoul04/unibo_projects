package a03a.e1;

import java.util.LinkedList;
import java.util.List;
import java.util.ListIterator;
import java.util.Optional;
import java.util.function.Function;
import java.util.stream.Stream;

public class WindowingFactoryImpl implements WindowingFactory {

    private static record WindowingImpl<X, Y>(List<X> elements, Function<List<X>, Optional<Y>> fun) implements Windowing<X, Y> {
        @Override
        public Optional<Y> process(X x) {
            elements.add(x);
            return fun.apply(elements);
        }
    }

    private <X, Y> Windowing<X, Y> genericWindowing(Function<List<X>, Optional<Y>> fun) {
        return new WindowingImpl<>(new LinkedList<>(), fun);
    }

    @Override
    public <X> Windowing<X, X> trivial() {
        return genericWindowing(t -> Optional.of(t.getLast()));
    }

    @Override
    public <X> Windowing<X, Pair<X, X>> pairing() {
        return genericWindowing(t -> {
            final ListIterator<X> it = t.listIterator(t.size());
            X e1 = null;
            X e2 = null;
            if (it.hasPrevious()) {
                e2 = it.previous();
            }
            if (it.hasPrevious()) {
                e1 = it.previous();
            }
            return e1 != null && e2 != null ? Optional.of(new Pair<>(e1, e2)) : Optional.empty();
        });
    }

    @Override
    public Windowing<Integer, Integer> sumLastFour() {
        return genericWindowing(t -> {
            final ListIterator<Integer> it = t.listIterator(t.size());
            int sum = 0;
            for (int i = 0; it.hasPrevious() && i < 4; i++) {
                sum = sum + it.previous();
            }
            return t.size() >= 4 ? Optional.of(sum) : Optional.empty();
        });
    }

    @Override
    public <X> Windowing<X, List<X>> lastN(int n) {
        return genericWindowing(t -> {
            final List<X> res = Stream.iterate(t.size() - 1, i -> i >= 0, i -> i - 1)
                .limit(n)
                .map(i -> t.get(i))
                .toList()
                .reversed();
            return res.size() == n
                ? Optional.of(res)
                : Optional.empty();
        });
    }

    @Override
    public Windowing<Integer, List<Integer>> lastWhoseSumIsAtLeast(int n) {
        return genericWindowing(t -> {
            final ListIterator<Integer> it = t.listIterator(t.size());
            final List<Integer> elements = new LinkedList<>();
            int elem = 0;
            int sum = 0;
            while (it.hasPrevious() && sum < n) {
                elem = it.previous();
                sum = sum + elem;
                elements.add(elem);
            }
            return sum >= n ? Optional.of(elements.reversed()) : Optional.empty();
        });
    }
}
