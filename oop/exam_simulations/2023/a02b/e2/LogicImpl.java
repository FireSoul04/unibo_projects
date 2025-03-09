package a02b.e2;

import java.util.Collections;
import java.util.HashSet;
import java.util.Set;

public class LogicImpl implements Logic {

    private final int size;
    private Set<Point> square = new HashSet<>();
    private Point center;
    private boolean exit = false;

    public LogicImpl(int size) {
        this.size = size;
    }

    @Override
    public void click(Point p) {
        if (square.isEmpty()) {
            center = p;
            createSquare();
        } else {
            if (topRight(p)) {
                move(new Point(1, -1));
            } else if (topLeft(p)) {
                move(new Point(-1, -1));
            } else if (bottomRight(p)) {
                move(new Point(1, 1));
            } else if (bottomLeft(p)) {
                move(new Point(-1, 1));
            } else if (p.equals(center)) {
                exit = true;
            }
        }
    }

    private void move(Point p) {
        int x = 0;
        int y = 0;
        if (p.x() > 0) {
            x = size - 1;
        }
        if (p.y() > 0) {
            y = size - 1;
        }
        center = new Point(x - p.x() * 2, y - p.y() * 2);
        createSquare();
    }

    private void createSquare() {
        square.clear();
        for (int y = center.y() - 2; y <= center.y() + 2; y++) {
            for (int x = center.x() - 2; x <= center.x() + 2; x++) {
                if ((center.x() - x) % 2 == 0 || (center.y() - y) % 2 == 0) {
                    square.add(new Point(x, y));
                }
            }
        }
    }

    private boolean topRight(Point p) {
        return p.equals(new Point(center.x() + 1, center.y() - 1));
    }

    private boolean topLeft(Point p) {
        return p.equals(new Point(center.x() - 1, center.y() - 1));
    }

    private boolean bottomRight(Point p) {
        return p.equals(new Point(center.x() + 1, center.y() + 1));
    }

    private boolean bottomLeft(Point p) {
        return p.equals(new Point(center.x() - 1, center.y() + 1));
    }

    @Override
    public Set<Point> getRectangle() {
        return Collections.unmodifiableSet(square);
    }

    @Override
    public boolean quit() {
        return exit;
    }
}
