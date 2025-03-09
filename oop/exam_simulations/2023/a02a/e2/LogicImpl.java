package a02a.e2;

import java.util.LinkedList;
import java.util.List;

public class LogicImpl implements Logic {

    private final List<Point> clicked = new LinkedList<>();
    private final int size;
    
    public LogicImpl(int size) {
        this.size = size;
    }

    @Override
    public boolean click(Point p) {
        if (isNotInGrid(p)) {
            if (clicked.size() == 4) {
                clicked.removeFirst();
            }
            clicked.add(p);
            return true;
        }
        return false;
    }

    @Override
    public boolean isInGrid(Point p) {
        return !isNotInGrid(p);
    }

    @Override
    public boolean isNotInGrid(Point p) {
        return p.y() % 2 == 0 && p.x() % 2 == 0;
    }

    @Override
    public boolean quit() {
        boolean exit = true;
        Point p = new Point(size, size);
        for (Point t : clicked) {
            p = new Point(Math.min(t.x(), p.x()), Math.min(t.y(), p.y()));
        }
        for (Point t : clicked) {
            if (!t.equals(p) && t.x() - 2 != p.x() && t.y() - 2 != p.y()) {
                exit = false;
            }
        }
        return exit && clicked.size() == 4;
    }
}
