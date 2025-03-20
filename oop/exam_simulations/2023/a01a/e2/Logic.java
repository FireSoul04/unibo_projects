package a01a.e2;

import java.util.Map;

public interface Logic {

    record Point(int x, int y) {
    }

    Map<Point, Integer> click(Point p);

    boolean quit();
}
