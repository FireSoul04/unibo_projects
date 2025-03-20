package a02b.e2;

import java.util.*;

public class LogicImpl implements Logic {

    private final Set<Position> cells = new HashSet<>();
    private final Set<Position> disabledCells = new HashSet<>();
    private final int size;
    private boolean check = false;

    public LogicImpl(final int size) {
        this.size = size;
    }

    @Override
    public boolean click(Position p) {
        if (cells.contains(p)) {
            cells.remove(p);
        } else {
            cells.add(p);
        }
        return cells.contains(p);
    }

    @Override
    public Set<Position> checkRestart() {
        if (!check) {
            check = validDiagonal();
        } else {
            restart();
            check = false;
            return null;
        }
        return Collections.unmodifiableSet(disabledCells);
    }

    private boolean areInTheSameDiagonal(final Position p1, final Position p2) {
        int dx = p1.x() - p2.x();
        int dy = p1.y() - p2.y();
        return dx == dy;
    }

    private boolean validDiagonal() {
        int count;
        for (final var x1 : cells) {
            count = 0;
            for (final var x2 : cells) {
                if (areInTheSameDiagonal(x2, x1)) {
                    count++;
                }
            }
            if (count == 3) {
                disableDiagonal(x1);
                return true;
            }
        }
        return false;
    }

    private void disableDiagonal(final Position p) {
        var point = new Position(p.x() - Math.min(p.x(), p.y()), p.y() - Math.min(p.x(), p.y()));
        while (!isOutOfBounds(point)) {
            disabledCells.add(point);
            point = point.sum(new Position(1, 1));
        }
    }

    private boolean isOutOfBounds(final Position p) {
        return p.x() < 0 || p.x() >= size || p.y() < 0 || p.y() >= size;
    }

    private void restart() {
        cells.clear();
        disabledCells.clear();
    }
}
