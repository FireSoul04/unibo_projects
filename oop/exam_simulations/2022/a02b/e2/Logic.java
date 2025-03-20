package a02b.e2;

import java.util.Set;

public interface Logic {

    boolean click(Position p);

    Set<Position> checkRestart();
}
