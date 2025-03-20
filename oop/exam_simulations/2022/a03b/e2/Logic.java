package a03b.e2;

import java.util.Map;

public interface Logic {

    enum Player {
        HUMAN,
        COMPUTER
    };
    
    boolean click(Position p);

    Map<Position, Player> pawns();

    void reset();

    boolean doReset();
}
