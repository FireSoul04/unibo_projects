package a06.e2;

import java.util.*;

public interface Logic {

    Pair<Position, Position> click(Position p);

    Map<Position, Integer> flippedCards();

    boolean isOver();
}
