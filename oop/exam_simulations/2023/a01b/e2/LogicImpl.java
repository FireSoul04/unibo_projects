package a01b.e2;

import java.util.*;

public class LogicImpl implements Logic {

    private final int size;
    private List<Point> clickedCells = new LinkedList<>();
    private boolean goRight = false;

    public LogicImpl(int size) {
        this.size = size;
    }

    @Override
    public int click(Point p) {
        if (clickedCells.size() < 5) {
            clickedCells.add(p);
            return clickedCells.size();
        } else {
            if (goRight || clickedCells.stream().anyMatch(t -> isOverLeftBorder(t))) {
                translateRight();
                goRight = true;
            } else {
                translateLeft();
            }
            return 0;
        }
    }

    private boolean isOverLeftBorder(Point p) {
        return p.x() <= 0 || p.y() <= 0;
    }

    private boolean isOverRightBorder(Point p) {
        return p.x() >= size || p.y() >= size;
    }

    private void translateRight() {
        translate(1);
    }

    private void translateLeft() {
        translate(-1);
    }

    private void translate(int direction) {
        clickedCells = clickedCells.stream().map(t -> new Point(t.x() + direction, t.y())).toList();
    }

    @Override
    public List<Point> getClickedPoints() {
        return Collections.unmodifiableList(clickedCells);
    }

    @Override
    public boolean quit() {
        return clickedCells.stream().anyMatch(t -> isOverRightBorder(t));
    }
}
