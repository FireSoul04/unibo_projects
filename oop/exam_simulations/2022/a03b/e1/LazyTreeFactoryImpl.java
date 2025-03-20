package a03b.e1;

import java.util.*;
import java.util.function.*;

public class LazyTreeFactoryImpl implements LazyTreeFactory {

    private static abstract class LazyTreeImpl<X> implements LazyTree<X> {
        private final X root;

        public LazyTreeImpl(final X root) {
            this.root = root;
        }

        @Override
        public boolean hasRoot() {
            return root != null;
        }

        @Override
        public X root() {
            return root;
        }
    }

    private <X> LazyTree<X> generic(X root, UnaryOperator<X> left, UnaryOperator<X> right) {
        return new LazyTreeImpl<X>(root) {
            @Override
            public LazyTree<X> left() {
                return generic(left.apply(root), left, right);
            }

            @Override
            public LazyTree<X> right() {
                return generic(right.apply(root), left, right);
            }
        };
    }

    @Override
    public <X> LazyTree<X> constantInfinite(X value) {
        return generic(value, t -> value, t -> value);
    }

    @Override
    public <X> LazyTree<X> fromMap(X root, Map<X, Pair<X, X>> map) {
        return generic(
            root,
            t -> map.entrySet().stream().filter(e -> e.getKey().equals(t)).map(e -> e.getValue().getX()).findFirst().orElse(null),
            t -> map.entrySet().stream().filter(e -> e.getKey().equals(t)).map(e -> e.getValue().getY()).findFirst().orElse(null)
        );
    }

    @Override
    public <X> LazyTree<X> cons(Optional<X> root, Supplier<LazyTree<X>> leftSupp, Supplier<LazyTree<X>> rightSupp) {
        return new LazyTreeImpl<X>(root.orElse(null)) {
            @Override
            public LazyTree<X> left() {
                return leftSupp.get();
            }

            @Override
            public LazyTree<X> right() {
                return rightSupp.get();
            }
        };
    }

    @Override
    public <X> LazyTree<X> fromTwoIterations(X root, UnaryOperator<X> leftOp, UnaryOperator<X> rightOp) {
        return generic(root, leftOp, rightOp);
    }

    @Override
    public <X> LazyTree<X> fromTreeWithBound(LazyTree<X> tree, int bound) {
        return bound > 0
            ? cons(Optional.of(tree.root()), () -> fromTreeWithBound(tree.left(), bound - 1), () -> fromTreeWithBound(tree.right(), bound - 1))
            : cons(Optional.empty(), () -> null, () -> null);
    }

}
