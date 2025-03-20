package a03a.e2;

import java.util.Set;

public interface Logic {

    Set<Point> click(Point p);

    Point target();

    boolean quit();
}
