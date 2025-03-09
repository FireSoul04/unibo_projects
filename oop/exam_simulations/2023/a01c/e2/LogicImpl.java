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
            start = clickedCells.stream().toList().get(0);
            end = clickedCells.stream().toList().get(1);    
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
        int x1 = start.x();
        int y1 = start.y();
        int x2 = end.x();
        int y2 = end.y();
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
        int x1 = start.x();
        int y1 = start.y();
        int x2 = end.x();
        int y2 = end.y();
        int x = Math.min(x1, x2) - 1;
        int y = Math.min(y1, y2) - 1;
        int w = Math.max(x1, x2) + 1;
        int h = Math.max(y1, y2) + 1;

        start = new Point(x, y);
        end = new Point(w, h);
        
        drawRectangle();
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
        return this.rectangleCells.size() > 0
            && this.rectangleCells.stream().anyMatch(t -> t.x() >= size - 1 && t.y() >= size - 1)
            && this.rectangleCells.stream().anyMatch(t -> t.x() <= 0 && t.y() <= 0);
    }
}
