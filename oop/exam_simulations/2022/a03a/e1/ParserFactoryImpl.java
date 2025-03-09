package a03a.e1;

import java.util.*;
import java.util.function.Function;

public class ParserFactoryImpl implements ParserFactory {

    private <X> List<X> toList(Iterator<X> it) {
        final List<X> ret = new LinkedList<>();
        while (it.hasNext()) {
            ret.add(it.next());
        }
        return ret;
    }

    @Override
    public <X> Parser<X> fromFinitePossibilities(Set<List<X>> acceptedSequences) {
        return it -> {
            final List<X> list = toList(it);
            for (final var t : acceptedSequences) {
                if (list.equals(t)) {
                    return true;
                }
            }
            return false;
        };
    }

    @Override
    public <X> Parser<X> fromGraph(X x0, Set<Pair<X, X>> transitions, Set<X> acceptanceInputs) {
        return it -> {
            while (it.hasNext()) {
                final var e1 = it.next();
                final Pair<X, X> elem = new Pair<>(e1, it.hasNext() ? it.next() : null);
                if (elem.getY() == null) {
                    return acceptanceInputs.contains(elem.getX());
                } else if (acceptanceInputs.contains(elem.getY()) && it.hasNext()) {
                    return false;
                } else if (!transitions.contains(elem)) {
                    return false;
                }
            }
            return false;
        };
    }

    @Override
    public <X> Parser<X> fromIteration(X x0, Function<X, Optional<X>> next) {
        return it -> {
            if (!(it.hasNext() && x0.equals(it.next()))) {
                return false;
            }
            var opt = next.apply(x0);
            while (it.hasNext() && opt.isPresent()) {
                final var elem = opt.get();
                opt = next.apply(elem);
                if (!it.next().equals(elem)) {
                    return false;
                }
            }
            return !it.hasNext() && !opt.isPresent();
        };
    }

    @Override
    public <X> Parser<X> recursive(Function<X, Optional<Parser<X>>> nextParser, boolean isFinal) {
        return it -> {
            if (!it.hasNext() && isFinal) {
                return true;
            }
            while (it.hasNext() && nextParser.apply(it.next()).isPresent())
                ;
            return it.hasNext();
        };
    }

    @Override
    public <X> Parser<X> fromParserWithInitial(X x, Parser<X> parser) {
        return it -> {
            if (!(it.hasNext() && it.next().equals(x))) {
                return false;
            }
            return parser.accept(it);
        };
    }

}
