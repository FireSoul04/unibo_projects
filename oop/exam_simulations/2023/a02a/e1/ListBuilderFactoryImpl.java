package a02a.e1;

import java.util.List;
import java.util.stream.Stream;

public class ListBuilderFactoryImpl implements ListBuilderFactory {

    private class ListBuilderData<T> implements ListBuilder<T> {
        
        private final List<T> list;

        public ListBuilderData(Stream<T> stream) {
            this.list = stream.toList();
        }

        @Override
        public ListBuilder<T> add(List<T> list) {
            return new ListBuilderData<>(Stream.concat(this.list.stream(), list.stream()));
        }

        @Override
        public ListBuilder<T> concat(ListBuilder<T> lb) {
            return add(lb.build());
        }

        @Override
        public ListBuilder<T> replaceAll(T t, ListBuilder<T> lb) {
            return new ListBuilderData<>(list.stream().flatMap(a -> a.equals(t) ? lb.build().stream() : Stream.of(a)));
        }

        @Override
        public ListBuilder<T> reverse() {
            return new ListBuilderData<>(list.reversed().stream());
        }

        @Override
        public List<T> build() {
            return list;
        }
    }

    @Override
    public <T> ListBuilder<T> empty() {
        return new ListBuilderData<T>(Stream.of());
    }

    @Override
    public <T> ListBuilder<T> fromElement(T t) {
        return new ListBuilderData<>(Stream.of(t));
    }

    @Override
    public <T> ListBuilder<T> fromList(List<T> list) {
        return new ListBuilderData<>(list.stream());
    }

    @Override
    public <T> ListBuilder<T> join(T start, T stop, List<ListBuilder<T>> builderList) {
        var startStream = fromElement(start);
        var midStream = fromList(builderList.stream().flatMap(t -> t.build().stream()).toList());
        var stopStream = fromElement(stop);
        return new ListBuilderData<>(startStream.concat(midStream).concat(stopStream).build().stream());
    }

}
