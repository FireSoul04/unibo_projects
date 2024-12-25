package a01c.e2;

import java.util.Collections;
import java.util.HashSet;
import java.util.Set;

public class LogicImpl implements Logic {

    private final Set<Point> clickedCells = new HashSet<>();
    private final Set<Point> rectangleCells = new HashSet<>();
    private final int size;
    private Point start;
    private Point end;

    public LogicImpl(int size) {
        this.size = size;
    }

    @Override
    public int click(Point p) {
        int val = 0;
        if (getRectanglePoints()) {
            clickedCells.add(p);
            val = clickedCells.size();
        } else if (startDrawRectangle()) {
            drawRectangle();
        } else {
            expandRectangle();
        }

        return val;
    }

    private boolean getRectanglePoints() {
        return clickedCells.size() < 2;
    }

    private boolean startDrawRectangle() {
        return rectangleCells.isEmpty();
    }

    private void drawRectangle() {
        Point p1 = clickedCells.stream().toList().get(0);
        Point p2 = clickedCells.stream().toList().get(1);

        int x1 = p1.x();
        int y1 = p1.y();
        int x2 = p2.x();
        int y2 = p2.y();
        int x = Math.min(x1, x2);
        int y = Math.min(y1, y2);
        int w = Math.abs(x1 - x2);
        int h = Math.abs(y1 - y2);

        for (int i = 0; i <= w; i++) {
            for (int j = 0; j <= h; j++) {
                Point p = new Point(i + x, j + y);
                if (!clickedCells.contains(p)) {
                    rectangleCells.add(p);
                }
            }
        }
    }

    private void expandRectangle() {
        start = clickedCells.stream().toList().get(0);
        end = clickedCells.stream().toList().get(1);

        int x1 = p1.x();
        int y1 = p1.y();
        int x2 = p2.x();
        int y2 = p2.y();
        int x = Math.min(x1, x2) - 1;
        int y = Math.min(y1, y2) - 1;
        int w = Math.max(x1, x2) - 1;
        int h = Math.max(y1, y2) - 1;
        
        for (int i = 0; i <= w; i++) {
            for (int j = 0; j <= h; j++) {
                Point p = new Point(i + x, j + y);
                if (!clickedCells.contains(p)) {
                    rectangleCells.add(p);
                }
            }
        }
    }

    @Override
    public Set<Point> getClickedCells() {
        return Collections.unmodifiableSet(clickedCells);
    }

    @Override
    public Set<Point> getRectangleCells() {
        return Collections.unmodifiableSet(rectangleCells);
    }

    @Override
    public boolean quit() {
        return this.clickedCells.size() > size * size;
    }
}
