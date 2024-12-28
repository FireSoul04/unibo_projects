package a03a.e2;

import java.util.Collections;
import java.util.HashSet;
import java.util.Random;
import java.util.Set;

public class LogicImpl implements Logic {

    private final int width;
    private final int height;
    private final Point target;
    private boolean exit = false;
    private int direction = -1;

    public LogicImpl(int width, int height) {
        Random rand = new Random();
        this.width = width;
        this.height = height;
        this.target = new Point(width - 1, rand.nextInt(height));
    }

    @Override
    public Set<Point> click(Point p) {
        Set<Point> trace = new HashSet<>();
        direction = -1;
        int y = p.y();
        for (int x = p.x(); x < width; x++) {
            Point tracePoint = new Point(x, y);
            bounce(tracePoint);
            trace.add(tracePoint);
            y = y + direction;
            if (tracePoint.equals(target)) {
                exit = true;
            }
        }
        return Collections.unmodifiableSet(trace);
    }

    private void bounce(Point p) {
        if (isTop(p) || isBottom(p)) {
            direction = direction * -1;
        }
    }

    private boolean isTop(Point p) {
        return p.y() == height;
    }

    private boolean isBottom(Point p) {
        return p.y() == 0;
    }

    @Override
    public Point target() {
        return this.target;
    }

    @Override
    public boolean quit() {
        return exit;
    }
}
