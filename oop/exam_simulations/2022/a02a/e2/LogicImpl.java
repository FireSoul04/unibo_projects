package a02a.e2;

import java.util.*;

public class LogicImpl implements Logic {

    private final List<Position> diagonals = List.of(
        new Position(1, 1),
        new Position(-1, 1),
        new Position(1, -1),
        new Position(-1, -1)        
    );
    private final Set<Position> bishops = new HashSet<>();
    private final Set<Position> disabled = new HashSet<>();
    private final int size;

    public LogicImpl(final int size) {
        this.size = size;
    }

    @Override
    public Set<Position> click(final Position p) {
        bishops.add(p);
        return disabledCells(p);
    }

    private Set<Position> disabledCells(final Position p) {
        for (final Position diagonal : diagonals) {
            Position temp = p;
            while (!isOutOfBounds(temp)) {
                disabled.add(temp);
                temp = temp.sum(diagonal);
            }
            disabled.remove(p);
        }
        return disabled;
    }

    private boolean isOutOfBounds(final Position p) {
        return p.x() < 0 || p.x() >= size || p.y() < 0 || p.y() >= size;
    }

    @Override
    public boolean restart() {
        if (disabled.size() + bishops.size() == size * size) {
            disabled.clear();
            bishops.clear();
            return true;
        }
        return false;
    }
}
