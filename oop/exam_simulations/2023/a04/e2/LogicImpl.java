package a04.e2;

import java.util.HashSet;
import java.util.Iterator;
import java.util.Random;
import java.util.Set;

public class LogicImpl implements Logic {

    private final int size;
    private final Point startPoint;
    private final Set<Point> clickedPoints = new HashSet<>();
    private boolean stop = false;

    public LogicImpl(int width) {
        this.size = width;
        startPoint = new Point(new Random().nextInt(width), 0);
        clickedPoints.add(startPoint);
    }

    @Override
    public Point getStartingPoint() {
        return startPoint;
    }

    @Override
    public boolean click(Point p) {
        if (isTopRow(p)) {
            return false;
        } else if (!clickedPoints.contains(p)) {
            clickedPoints.add(p);
            stop = checkWin();
            return true;
        }
        return false;
    }

    private boolean isTopRow(Point p) {
        return p.y() == 0;
    }

    private boolean isBottomRow(Point p) {
        return p.y() == size - 1;
    }

    private boolean isDiagonal(Point p1, Point p2) {
        return p2.y() - p1.y() == 1
            && Math.abs(p1.x() - p2.x()) == 1;
    }

    private boolean checkWin() {
        Point p1 = startPoint;
        while (!isBottomRow(p1)) {
            Point p2 = null;
            Iterator<Point> it = clickedPoints.iterator();
            while (it.hasNext()) {
                Point p = it.next();
                if (isDiagonal(p1, p)) {
                    p2 = p;
                    break;
                }
            }
            if (p2 != null) {
                p1 = p2;
            } else {
                return false;
            }
        }
        return true;
    }

    @Override
    public boolean quit() {
        return stop;
    }
}
