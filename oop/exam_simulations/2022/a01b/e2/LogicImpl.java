package a01b.e2;

import java.util.*;

public class LogicImpl implements Logic {

    private final List<Position> diagonals = List.of(
        new Position(1, 1),
        new Position(1, -1),
        new Position(-1, 1),
        new Position(-1, -1)
    );
    private final Set<Position> clickedPoints = new HashSet<>();
    private final int size;
    private boolean exit = false;

    public LogicImpl(final int size) {
        this.size = size;
    }

    @Override
    public boolean click(final Position p) {
        toggleNeighbors(p);
        return clickedPoints.contains(p);
    }

    private void toggleNeighbors(final Position p) {
        int removedCells = 0;
        for (final var t : getDiagonalNeighbors(p)) {
            if (clickedPoints.contains(t)) {
                clickedPoints.remove(t);
                removedCells++;
            } else {
                clickedPoints.add(t);
            }
        }
        exit = removedCells == 3;
    }

    private Set<Position> getDiagonalNeighbors(final Position p) {
        final Set<Position> neighbors = new HashSet<>();
        diagonals.forEach(t -> {
            if (!isOutOfBounds(p.sum(t))) {
                neighbors.add(p.sum(t));
            }
        });
        return neighbors;
    }

    private boolean isOutOfBounds(final Position p) {
        return p.x() < 0 || p.x() >= size || p.y() < 0 || p.y() >= size;
    }

    @Override
    public Set<Position> points() {
        return Collections.unmodifiableSet(clickedPoints);
    }

    @Override
    public boolean quit() {
        return exit;
    }

}
