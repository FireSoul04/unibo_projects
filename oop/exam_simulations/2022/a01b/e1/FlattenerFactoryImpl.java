package a01b.e1;

import java.util.*;
import java.util.function.Function;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class FlattenerFactoryImpl implements FlattenerFactory {

    @Override
    public Flattener<Integer, Integer> sumEach() {
        return l -> l.stream().map(t -> t.stream().mapToInt(e -> e).sum()).toList();
    }

    @Override
    public <X> Flattener<X, X> flattenAll() {
        return l -> l.stream().flatMap(t -> t.stream()).toList();
    }

    @Override
    public Flattener<String, String> concatPairs() {
        return l -> Stream.iterate(0, i -> i < l.size(), i -> i + 2)
            .map(i -> new Pair<>(l.get(i), i + 1 < l.size() ? l.get(i + 1) : List.of("")))
            .map(t -> Stream.concat(t.getX().stream(), t.getY().stream()).toList())
            .map(t -> t.stream().collect(Collectors.joining()))
            .toList();
    }
    
    @Override
    public <I, O> Flattener<I, O> each(Function<List<I>, O> mapper) {
        return l -> l.stream().map(t -> mapper.apply(t)).toList();
    }

    @Override
    public Flattener<Integer, Integer> sumVectors() {
        return l -> Stream.iterate(0, i -> i < l.get(0).size(), i -> i + 1)
            .map(i -> l.stream().mapToInt(t -> t.get(i)).sum())
            .toList();
    }

}
