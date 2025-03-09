package a03a.e2;

import java.util.*;

public class LogicImpl implements Logic {

    private final List<Position> directions = List.of(
        new Position(1, 0),
        new Position(0, 1),
        new Position(-1, 0),
        new Position(0, -1)
    );
    private final int size;
    private final Random rand = new Random();
    private Position player;
    private Position computer;
    private boolean over;

    public LogicImpl(final int size) {
        this.size = size;
        this.restart();
    }

    private Position getRandomPosition() {
        return new Position(rand.nextInt(size), rand.nextInt(size));
    }

    private Position getRandomDirection() {
        return directions.get(rand.nextInt(directions.size()));
    }

    @Override
    public boolean click(final Position p) {
        if (validPosition(p)) {
            player = p;
            if (player.equals(computer)) {
                System.out.println("umano vince");
                over = true;
            } else {
                moveComputer();
            }
            return true;
        }
        return false;
    }

    private void moveComputer() {
        if (validPosition(computer)) {
            computer = player;
            System.out.println("computer vince");
            over = true;
        } else {
            final int r = rand.nextInt(1, size);
            Position direction;
            do {
                direction = getRandomDirection();
            } while (isOutOfBounds(computer.sum(direction)));
            for (int i = 0; i < r && !isOutOfBounds(computer.sum(direction)); i++) {
                computer = computer.sum(direction);
            }
        }
    }

    private boolean isOutOfBounds(final Position p) {
        return p.x() < 0 || p.x() >= size || p.y() < 0 || p.y() >= size;
    }

    private boolean validPosition(final Position p) {
        return !player.equals(p) && (player.x() == p.x() || player.y() == p.y());
    }

    @Override
    public Position player() {
        return player;
    }

    @Override
    public Position computer() {
        return computer;
    }

    @Override
    public boolean doRestart() {
        return over;
    }

    @Override
    public void restart() {
        over = false;
        computer = getRandomPosition();
        do {
            player = getRandomPosition();
        } while (player.equals(computer));
    }
}
