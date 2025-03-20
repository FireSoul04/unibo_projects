package a01b.e2;

import java.util.Set;

public interface Logic {

    boolean click(Position p);

    Set<Position> points();

    boolean quit();
}
