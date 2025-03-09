package a06.e1;

import java.util.LinkedList;
import java.util.List;
import java.util.function.Function;
import java.util.function.Predicate;
import java.util.stream.Stream;

public class ZipCombinerFactoryImpl implements ZipCombinerFactory {

    @Override
    public <X, Y> ZipCombiner<X, Y, Pair<X, Y>> classical() {
        return (l1, l2) -> Stream.iterate(0, i -> i < l1.size(), i -> i + 1).map(i -> new Pair<>(l1.get(i), l2.get(i))).toList();
    }

    @Override
    public <X, Y, Z> ZipCombiner<X, Y, Z> mapFilter(Predicate<X> predicate, Function<Y, Z> mapper) {
        return (l1, l2) -> Stream.iterate(0, i -> i < l1.size(), i -> i + 1).filter(i -> predicate.test(l1.get(i))).map(i -> l2.get(i)).map(t -> mapper.apply(t)).toList();
    }

    @Override
    public <Y> ZipCombiner<Integer, Y, List<Y>> taker() {
        return (l1, l2) -> {
            final List<List<Y>> ret = new LinkedList<>();
            int index = 0;
            for (int i = 0; i < l1.size(); i++) {
                final List<Y> l = new LinkedList<>();
                final int start = index;
                for (int j = 0; j < l1.get(i); j++) {
                    l.add(l2.get(start + j));
                    index++;
                }
                ret.add(l);
            }
            return ret;
        };
    }

    @Override
    public <X> ZipCombiner<X, Integer, Pair<X, Integer>> countUntilZero() {
        return (l1, l2) -> {
            final List<Pair<X, Integer>> ret = new LinkedList<>();
            int index = 0;
            for (int i = 0; i < l1.size(); i++) {
                final int start = index;
                for (int j = 0; j < l2.size() && l2.get(start + j) != 0; j++) {
                    index++;
                }
                ret.add(new Pair<X,Integer>(l1.get(i), index - start));
                if (l2.get(index) == 0) {
                    index++;
                }
            }
            return ret;
        };
    }
}
