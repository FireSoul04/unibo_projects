package a03b.e2;

import java.util.Set;

public interface Logic {

    Point target();

    Set<Point> click(Point p);

    boolean quit();
}
