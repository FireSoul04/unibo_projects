package a01c.e2;

import java.util.Set;

public interface Logic {

    int click(Point p);

    Set<Point> getClickedCells();

    Set<Point> getRectangleCells();

    boolean quit();
}