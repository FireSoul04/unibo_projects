package a03b.e2;

import java.util.HashSet;
import java.util.Random;
import java.util.Set;

public class LogicImpl implements Logic {

    private final int width;
    private final int height;
    private final Point target;
    private Set<Point> clickedPoints = new HashSet<>();

    public LogicImpl(int width, int height) {
        Random r = new Random();
        this.width = width;
        this.height = height;
        this.target = new Point(r.nextInt(width), r.nextInt(height));
    }

    public Point target() {
        return target;
    }

    @Override
    public Set<Point> click(Point p) {
        drawTriangle(p);
        return clickedPoints;
    }

    private void drawTriangle(Point p) {
        int count = 0;
        int x = p.x();
        Set<Point> triangle = new HashSet<>();
        while (triangle.stream().noneMatch(this::isOnBorder)) {
            for (int y = p.y() - count; y <= p.y() + count; y++) {
                triangle.add(new Point(x, y));
            }
            x++;
            count++;
        }
        clickedPoints.addAll(triangle);
    }

    private boolean isOnBorder(Point p) {
        return p.y() == 0 || p.y() == height - 1;
    }

    @Override
    public boolean quit() {
        return clickedPoints.stream().anyMatch(t -> t.equals(target));
    }
}
