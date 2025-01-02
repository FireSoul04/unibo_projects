package a04.e1;

import java.util.LinkedList;
import java.util.List;
import java.util.Optional;
import java.util.function.Function;
import java.util.function.Predicate;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class ListExtractorFactoryImpl implements ListExtractorFactory {

    @Override
    public <X> ListExtractor<X, Optional<X>> head() {
        return l -> l.stream().findFirst();
    }

    @Override
    public <X, Y> ListExtractor<X, List<Y>> collectUntil(Function<X, Y> mapper, Predicate<X> stopCondition) {
        return l -> {
            List<X> out = new LinkedList<>();
            for (var elem : l) {
                if (stopCondition.test(elem)) {
                    break;
                }
                out.add(elem);
            }
            return out.stream().map(t -> mapper.apply(t)).toList();
        };
    }

    @Override
    public <X> ListExtractor<X, List<List<X>>> scanFrom(Predicate<X> startCondition) {
        return l -> {
            List<List<X>> out = new LinkedList<>();
            int i;
            for (i = 0; i < l.size(); i++) {
                var elem = l.get(i);
                if (startCondition.test(elem)) {
                    break;
                }
            }
            int start = i;
            for (; i < l.size(); i++) {
                List<X> list = new LinkedList<>();
                for (int j = start; j < l.size() && j < i + 1; j++) {
                    list.add(l.get(j));
                }
                out.add(list);
            }
            return out;
        };
    }

    @Override
    public <X> ListExtractor<X, Integer> countConsecutive(X x) {
        return l -> {
            int consecutive = 0;
            boolean first = false;
            for (var elem : l) {
                if (elem.equals(x)) {
                    consecutive++;
                    first = true;
                } else if (first) {
                    break;
                }
            }
            return consecutive;
        };
    }

}
