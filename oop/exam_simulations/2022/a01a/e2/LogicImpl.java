package a01a.e2;

import java.util.*;

public class LogicImpl implements Logic {

    private final List<Position> clicks = new ArrayList<>();
    private final Set<Position> clickedPoints = new HashSet<>();
    private final int size;

    public LogicImpl(int size) {
        this.size = size;
    }

    @Override
    public boolean click(final Position p) {
        if (clickedPoints.contains(p)) {
            clickedPoints.remove(p);
            clicks.clear();
            return false;
        } else {
            clickedPoints.add(p);
            clicks.add(p);
            return true;
        }
    }

    @Override
    public boolean quit() {
        if (clicks.size() >= 3) {
            var l = clicks.subList(clicks.size() - 3, clicks.size());
            var oldDirection = new Position(0, 0);
            for (int i = 0; i < l.size() - 1; i++) {
                int dx = l.get(i).x() - l.get(i + 1).x();
                int dy = l.get(i).y() - l.get(i + 1).y();
                var direction = new Position(dx, dy);
                if (direction.equals(oldDirection)) {
                    return true;
                }
                oldDirection = direction;
            }
        }
        return false;
    }
}
