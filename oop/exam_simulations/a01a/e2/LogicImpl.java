package a01a.e2;

import java.util.*;

public class LogicImpl implements Logic {

    private final int size;
    private Map<Point, Integer> clicked = new HashMap<>();
    private boolean translate = false;

    public LogicImpl(final int size) {
        this.size = size;
    }

    @Override
    public Map<Point, Integer> click(final Point p) {
        if (this.translate || this.isAdjacent(p)) {
            this.translate();
        } else {
            int val = 0;
            if (this.clicked.containsKey(p)) {
                val = this.clicked.get(p);
            }
            final int newVal = val + 1;
            this.clicked.put(p, newVal);
        }
        return this.clicked;
    }

    private boolean adjacent(final Point p1, final Point p2) {
        return !p1.equals(p2)
            && Math.abs(p1.x() - p2.x()) <= 1
            && Math.abs(p1.y() - p2.y()) <= 1;
    }

    private boolean isAdjacent(final Point p) {
        for (final Point p1 : this.clicked.keySet()) {
            if (this.adjacent(p1, p)) {
                this.translate = true;
                return true;
            }
        }
        return false;
    }

    private void translate() {
        final Map<Point, Integer> newMap = new HashMap<>();
        for (final var entry : this.clicked.entrySet()) {
            final Point p = entry.getKey();
            final int v = entry.getValue();
            newMap.put(new Point(p.x() + 1, p.y() - 1), v);
        }
        this.clicked = newMap;
    }

    @Override
    public boolean quit() {
        return this.clicked.keySet()
            .stream()
            .anyMatch(t -> t.x() >= size || t.y() < 0);
    }

}
