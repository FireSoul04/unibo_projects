package a02c.e1;

import java.util.LinkedList;
import java.util.List;
import java.util.ListIterator;

public class ReplacersFactoryImpl implements ReplacersFactory {

    @Override
    public <T> Replacer<T> noReplacement() {
        return (list, elem) -> List.of();
    }

    @Override
    public <T> Replacer<T> duplicateFirst() {
        return (list, elem) -> {
            final List<T> concatenated = new LinkedList<>();
            boolean found = false;
            for (final T e : list) {
                concatenated.add(e);
                if (!found && e.equals(elem)) {
                    concatenated.add(elem);
                    found = true;
                }
            }
            return found ? List.of(concatenated) : List.of();
        };
    }

    @Override
    public <T> Replacer<T> translateLastWith(List<T> target) {
        return (list, elem) -> {
            final List<T> concatenated = new LinkedList<>();
            final ListIterator<T> it = list.listIterator(list.size());
            boolean found = false;
            while (it.hasPrevious()) {
                final var e = it.previous();
                if (!found && e.equals(elem)) {
                    concatenated.addAll(target);
                    found = true;
                } else {
                    concatenated.add(e);
                }
            }
            return found ? List.of(concatenated.reversed()) : List.of();
        };
    }

    @Override
    public <T> Replacer<T> removeEach() {
        return (list, elem) -> {
            final List<List<T>> solutions = new LinkedList<>();
            for (int i = 0; i < list.size(); i++) {
                if (list.get(i).equals(elem)) {
                    final List<T> solution = new LinkedList<>(list);
                    solution.remove(i);
                    solutions.add(solution);
                }
            }
            return solutions;
        };
    }

    @Override
    public <T> Replacer<T> replaceEachFromSequence(List<T> sequence) {
        return (list, elem) -> {
            final List<List<T>> solutions = new LinkedList<>();
            int j = 0;
            for (int i = 0; i < list.size(); i++) {
                if (j < sequence.size() && list.get(i).equals(elem)) {
                    final List<T> solution = new LinkedList<>(list);
                    solution.remove(i);
                    solution.add(i, sequence.get(j++));
                    solutions.add(solution);
                }
            }
            System.out.println();
            return solutions;
        };
    }

}
