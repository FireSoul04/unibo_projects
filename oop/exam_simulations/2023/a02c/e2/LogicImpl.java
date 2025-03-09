package a02c.e2;

import java.util.Collections;
import java.util.HashSet;
import java.util.Set;

public class LogicImpl implements Logic {

    private final int size;
    private Point center = null;
    private Point topRight = null;
    private Point topLeft = null;
    private Point bottomRight = null;
    private Point bottomLeft = null;
    private Set<Point> rectangle = new HashSet<>();

    public LogicImpl(int size) {
        this.size = size;
    }

    @Override
    public void click(Point p) {
        if (center == null) {
            center = p;
            topRight = new Point(p.x() + 1, p.y() - 1);
            topLeft = new Point(p.x() - 1, p.y() - 1);
            bottomRight = new Point(p.x() + 1, p.y() + 1);
            bottomLeft = new Point(p.x() - 1, p.y() + 1);
        } else {
            if (isTopLeft(p)) {
                topLeft = new Point(p.x() - 1, p.y() - 1);
                topRight = new Point(topRight.x(), topRight.y() - 1);
                bottomLeft = new Point(bottomLeft.x() - 1, bottomLeft.y());
            } else if (isTopRight(p)) {
                topRight = new Point(p.x() + 1, p.y() - 1);
                topLeft = new Point(topLeft.x(), topLeft.y() - 1);
                bottomRight = new Point(bottomRight.x() + 1, bottomRight.y());
            } else if (isBottomLeft(p)) {
                bottomLeft = new Point(p.x() - 1, p.y() + 1);
                topLeft = new Point(topLeft.x() - 1, topLeft.y());
                bottomRight = new Point(bottomRight.x(), bottomRight.y() + 1);
            } else if (isBottomRight(p)) {
                bottomRight = new Point(p.x() + 1, p.y() + 1);
                topRight = new Point(topRight.x() + 1, topRight.y());
                bottomLeft = new Point(bottomLeft.x(), bottomLeft.y() + 1);
            }
        }
        drawRect();
    }

    private void drawRect() {
        rectangle.clear();
        for (int y = topLeft.y(); y <= bottomRight.y(); y++) {
            for (int x = topLeft.x(); x <= bottomRight.x(); x++) {
                if (x == topLeft.x() || x == bottomRight.x() || y == topLeft.y() || y == bottomRight.y()) {
                    rectangle.add(new Point(x, y));
                }
            }
        }
    }

    private boolean isTopRight(Point p) {
        return topRight.equals(p);
    }

    private boolean isTopLeft(Point p) {
        return topLeft.equals(p);
    }

    private boolean isBottomRight(Point p) {
        return bottomRight.equals(p);
    }

    private boolean isBottomLeft(Point p) {
        return bottomLeft.equals(p);
    }

    @Override
    public Set<Point> rectangle() {
        return Collections.unmodifiableSet(this.rectangle);
    }

    @Override
    public boolean quit() {
        return rectangle.stream().anyMatch(t -> t.x() <= 0 || t.x() >= size - 1 || t.y() <= 0 || t.y() >= size - 1);
    }
}
