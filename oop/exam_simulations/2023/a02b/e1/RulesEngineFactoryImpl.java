package a02b.e1;

import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.function.Function;
import java.util.stream.Stream;

public class RulesEngineFactoryImpl implements RulesEngineFactory {

    private static class RulesEngineImpl<T> implements RulesEngine<T> {

        private final Function<List<T>, List<List<T>>> fun;
        private Iterator<List<T>> solutionsIterator;

        public RulesEngineImpl(Function<List<T>, List<List<T>>> fun) {
            this.fun = fun;
        }

        @Override
        public void resetInput(List<T> input) {
            solutionsIterator = fun.apply(input).iterator();
        }

        @Override
        public boolean hasOtherSolutions() {
            return solutionsIterator.hasNext();
        }

        @Override
        public List<T> nextSolution() {
            return solutionsIterator.next();
        }
    }

    private <T> List<T> replacePositions(int index, List<T> source, List<T> newElements) {
        var l = new LinkedList<>(source);
        l.remove(index);
        var it = newElements.listIterator(newElements.size());
        while (it.hasPrevious()){
            l.add(index, it.previous());
        }
        return l;
    }

    @Override
    public <T> List<List<T>> applyRule(Pair<T, List<T>> rule, List<T> input) {
        return Stream
            .iterate(0, i -> i < input.size(), i -> i + 1)
            .flatMap(i -> input.get(i).equals(rule.get1()) ? Stream.of(replacePositions(i, input, rule.get2())) : Stream.empty())
            .toList();
    }

    @Override
    public <T> RulesEngine<T> singleRuleEngine(Pair<T, List<T>> rule) {
        return new RulesEngineImpl<>(t -> {
            List<T> res = new LinkedList<>();
            for (T elem : t) {
                if (elem.equals(rule.get1())) {
                    res.addAll(rule.get2());
                } else {
                    res.add(elem);
                }
            }
            return List.of(res);
        });
    }

    @Override
    public <T> RulesEngine<T> cascadingRulesEngine(Pair<T, List<T>> baseRule, Pair<T, List<T>> cascadeRule) {
        return new RulesEngineImpl<>(t -> {
            List<T> res = new LinkedList<>();
            for (T elem : t) {
                if (elem.equals(baseRule.get1())) {
                    res.addAll(baseRule.get2());
                } else {
                    res.add(elem);
                }
            }
            List<T> res2 = new LinkedList<>();
            for (T elem : res) {
                if (elem.equals(cascadeRule.get1())) {
                    res2.addAll(cascadeRule.get2());
                } else {
                    res2.add(elem);
                }
            }
            return List.of(res2);
        });
    }

    @Override
    public <T> RulesEngine<T> conflictingRulesEngine(Pair<T, List<T>> rule1, Pair<T, List<T>> rule2) {
        return null;
    }
}
