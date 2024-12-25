package a01b.e2;

import java.util.List;

public interface Logic {

    public static record Point(int x, int y) {
    } 

    int click(Point p);

    List<Point> getClickedPoints();

    boolean quit();
}