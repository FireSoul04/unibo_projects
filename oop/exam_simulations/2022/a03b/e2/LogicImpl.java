package a03b.e2;

import java.util.*;

public class LogicImpl implements Logic {

    private final int size;
    private final Random rand = new Random();
    private final Map<Position, Player> pawns = new HashMap<>();

    public LogicImpl(final int size) {
        this.size = size;
        reset();
    }

    @Override
    public boolean click(final Position p) {
        if (isHumanHere(p)) {
            return movePawn(p);
        }
        return false;
    }

    private boolean movePawn(final Position p) {
        final Position upPos = p.sum(new Position(0, -1));
        final Position diagLeft = p.sum(new Position(-1, -1));
        final Position diagRight = p.sum(new Position(1, -1));
        Position nextPos = null;
        if (isComputerHere(diagLeft) && isComputerHere(diagRight)) {
            nextPos = rand.nextInt(2) == 0 ? diagLeft : diagRight;
            pawns.remove(nextPos);
        } else if (isComputerHere(diagLeft)) {
            nextPos = diagLeft;
            pawns.remove(nextPos);
        } else if (isComputerHere(diagRight)) {
            nextPos = diagRight;
            pawns.remove(nextPos);
        } else if (!isComputerHere(upPos) && !isHumanHere(upPos)) {
            nextPos = upPos;
        }
        if (nextPos != null && !isOutOfBounds(nextPos)) {
            pawns.remove(p);
            pawns.put(nextPos, Player.HUMAN);
            return true;
        }
        return false;
    }

    private boolean isHumanHere(final Position p) {
        return pawns.containsKey(p) && pawns.get(p).equals(Player.HUMAN);
    }

    private boolean isComputerHere(final Position p) {
        return pawns.containsKey(p) && pawns.get(p).equals(Player.COMPUTER);
    }

    private boolean isOutOfBounds(final Position p) {
        return p.y() < 0 || p.y() >= size;
    }

    @Override
    public Map<Position, Player> pawns() {
        return Collections.unmodifiableMap(pawns);
    }

    @Override
    public void reset() {
        pawns.clear();
        for (int x = 0; x < size; x++) {
            pawns.put(new Position(x, size - 1), Player.HUMAN);
            pawns.put(new Position(x, rand.nextInt(2)), Player.COMPUTER);
        }
    }

    @Override
    public boolean doReset() {
        return pawns.values().stream().filter(t -> t.equals(Player.COMPUTER)).count() == 0;
    }
}
