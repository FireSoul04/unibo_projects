package a01a.e1;

import java.util.Iterator;
import java.util.LinkedHashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.function.BiFunction;
import java.util.function.Function;
import java.util.function.Predicate;
import java.util.stream.Stream;

public class SubsequenceCombinerFactoryImpl implements SubsequenceCombinerFactory {

    private <X, Y> List<Y> fromMap(List<X> input, Y start, BiFunction<Y, Integer, Y> fun, Function<Integer, Integer> index) {
        Map<Integer, Y> ret = new LinkedHashMap<>();
        Y result = start;
        for (int i = 0; i < input.size(); i++) {
            result = fun.apply(result, i);
            ret.put(index.apply(i), result);
        }
        return new LinkedList<>(ret.values());
    }

    @Override
    public SubsequenceCombiner<Integer, Integer> tripletsToSum() {
        return l -> fromMap(l, 0, (sum, i) -> i % 3 == 0 ? l.get(i) : sum + l.get(i), i -> i / 3);
    }

    @Override
    public <X> SubsequenceCombiner<X, List<X>> tripletsToList() {
        return l -> fromMap(l, new LinkedList<>(), (sublist, i) -> {
            if (i % 3 == 0) {
                List<X> ret = new LinkedList<>();
                ret.add(l.get(i));
                return ret;
            } else {
                sublist.add(l.get(i));
                return sublist;
            }
        }, i -> i / 3);
    }

    @Override
    public <X, Y> SubsequenceCombiner<X, Y> singleReplacer(Function<X, Y> function) {
        return l -> fromMap(l, null, (a, i) -> function.apply(l.get(i)), Function.identity());
    }

    private <X, Y> List<Y> fromIterator(Stream<X> input, Predicate<X> predicate, Function<List<X>, Y> fun) {
        Iterator<X> it = input.iterator();
        List<Y> solution = new LinkedList<>();
        List<X> group = new LinkedList<>();
        while (it.hasNext()) {
            X elem = it.next();
            if (!predicate.test(elem)) {
                group.add(elem);
            } else if (it.hasNext()) {
                solution.add(fun.apply(group));
                group = new LinkedList<>();
            }
        }
        solution.add(fun.apply(group));
        return solution;
    }

    @Override
    public SubsequenceCombiner<Integer, Integer> countUntilZero() {
        return l -> fromIterator(l.stream(), t -> t == 0, t -> t.size());
    }

    @Override
    public SubsequenceCombiner<Integer, List<Integer>> cumulateToList(int threshold) {
        return l -> {
            List<List<Integer>> solution = new LinkedList<>();
            List<Integer> nums = new LinkedList<>();
            Iterator<Integer> it = l.iterator();
            while (it.hasNext()) {
                int num = it.next();
                nums.add(num);
                if (nums.stream().mapToInt(t -> t).sum() >= threshold || !it.hasNext()) {
                    solution.add(nums);
                    nums = new LinkedList<>();
                }
            }
            return solution;
        };
    }

}
