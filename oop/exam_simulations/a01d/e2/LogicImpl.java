package a01d.e2;

import java.util.LinkedList;
import java.util.List;

public class LogicImpl implements Logic {

    private List<Point> rectangle = new LinkedList<>();
    private int size;

    public LogicImpl(int size) {
        this.size = size;
    }

    @Override
    public void click(Point p) {
        if (rectangle.isEmpty()) {
            int x1 = p.x() - 2;
            int y1 = p.y() - 2;
            int x2 = p.x() + 2;
            int y2 = p.y() + 2;

            for (int y = y1; y <= y2; y++) {
                for (int x = x1; x <= x2; x++) {
                    rectangle.add(new Point(x, y));
                }
            }
        } else {
            if (isLeftEdge(p)) {
                move(new Point(-1, 0));
            } else if (isRightEdge(p)) {
                move(new Point(1, 0));
            }
            if (isTopEdge(p)) {
                move(new Point(0, -1));
            } else if (isBottomEdge(p)) {
                move(new Point(0, 1));
            }
        }
    }

    private void move(Point direction) {
        rectangle = rectangle.stream().map(t -> new Point(t.x() + direction.x(), t.y() + direction.y())).toList();
    }

    private boolean isLeftEdge(Point p) {
        return p.x() == 0;
    }

    private boolean isRightEdge(Point p) {
        return p.x() == size - 1;
    }

    private boolean isTopEdge(Point p) {
        return p.y() == 0;
    }

    private boolean isBottomEdge(Point p) {
        return p.y() == size - 1;
    }

    @Override
    public List<Point> getRectangle() {
        return rectangle;
    }

    @Override
    public boolean quit() {
        return rectangle.stream()
            .anyMatch(p -> p.x() < 0 || p.x() >= size || p.y() < 0 || p.y() >= size);
    }

}
