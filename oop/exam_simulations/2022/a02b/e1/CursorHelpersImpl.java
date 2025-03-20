package a02b.e1;

import java.util.*;
import java.util.function.BiPredicate;
import java.util.function.Consumer;
import java.util.stream.Stream;

public class CursorHelpersImpl implements CursorHelpers {

    private <X> Cursor<X> generic(Stream<X> input, BiPredicate<Iterator<X>, Integer> hasNext) {
        return new Cursor<X>() {
            Iterator<X> it = input.iterator();
            int index = 1;
            X elem = it.next();

            @Override
            public X getElement() {
                return elem;
            }

            @Override
            public boolean advance() {
                boolean canAdvance = hasNext.test(it, index);
                if (canAdvance) {
                    index++;
                    elem = it.next();
                }
                return canAdvance;
            }
        };
    }

    private <X> List<X> toList(Cursor<X> input) {
        List<X> ret = new LinkedList<>();
        do {
            ret.add(input.getElement());
        } while (input.advance());
        return ret;
    }

    @Override
    public <X> Cursor<X> fromNonEmptyList(List<X> list) {
        return generic(list.stream(), (it, i) -> it.hasNext());
    }

    @Override
    public Cursor<Integer> naturals() {
        return generic(Stream.iterate(0, i -> i < Integer.MAX_VALUE, i -> i + 1), (it, i) -> it.hasNext());
    }

    @Override
    public <X> Cursor<X> take(Cursor<X> input, int max) {
        return generic(toList(input).stream(), (it, i) -> it.hasNext() && i < max);
    }

    @Override
    public <X> void forEach(Cursor<X> input, Consumer<X> consumer) {
        toList(input).forEach(t -> consumer.accept(t));
    }

    @Override
    public <X> List<X> toList(Cursor<X> input, int max) {
        return toList(input).stream().limit(max).toList();
    }

}
