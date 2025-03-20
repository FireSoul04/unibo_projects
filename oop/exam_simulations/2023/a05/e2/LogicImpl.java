package a05.e2;

import java.util.List;
import java.util.Random;

public class LogicImpl implements Logic {

    private final List<Position> directions = List.of(
        new Position(-1, -1),
        new Position(-1, 0),
        new Position(-1, 1),
        new Position(0, 1),
        new Position(1, 1),
        new Position(1, 0),
        new Position(1, -1),
        new Position(0, -1)
    );
    private final Random rand = new Random();
    private final int size;
    private final Entity player;
    private final Entity enemy;
    private boolean over = false;

    public LogicImpl(int size) {
        this.size = size;
        this.enemy = new Entity(getRandomPosition()) {
            @Override
            protected Position whereToGo(Position position) {
                if (neighbor(enemy.position(), position) && canMove(position)) {
                    Position direction;
                    Position next;
                    do {
                        direction = getRandomDirection();
                        next = new Position(position().x() + direction.x(), position().y() + direction.y());
                    } while (isOutOfBounds(next) || neighbor(next, position) || next.equals(position));
                    return next;
                } else {
                    return position();
                }
            }

            private boolean canMove(Position position) {
                return !directions.stream().allMatch(t -> {
                    Position next = new Position(position().x() + t.x(), position().y() + t.y());
                    return isOutOfBounds(next) || neighbor(next, position) || next.equals(position);
                });
            }
        };
        Position playerPosition = getRandomPosition();
        while (neighbor(enemy.position(), playerPosition) || playerPosition.equals(enemy.position())) {
            playerPosition = getRandomPosition();
        }
        this.player = new Entity(playerPosition) {
            @Override
            protected Position whereToGo(Position position) {
                return position;
            }
        };
    }

    private boolean isOutOfBounds(Position p) {
        return p.x() < 0 || p.y() < 0 || p.x() >= size || p.y() >= size;
    }

    private Position getRandomPosition() {
        return new Position(rand.nextInt(size), rand.nextInt(size));
    }

    private Position getRandomDirection() {
        return directions.get(rand.nextInt(directions.size()));
    }

    @Override
    public boolean click(Position p) {
        if (neighbor(player.position(), p)) {
            player.move(p);
            enemy.move(p);
            if (player.position().equals(enemy.position())) {
                over = true;
            }
            return true;
        }
        return true;
    }

    private boolean neighbor(Position p1, Position p2) {
        return !p1.equals(p2)
            && Math.abs(p1.x() - p2.x()) <= 1
            && Math.abs(p1.y() - p2.y()) <= 1;
    }

    @Override
    public Entity getPlayer() {
        return player;
    }

    @Override
    public Entity getEnemy() {
        return enemy;
    }

    @Override
    public boolean isOver() {
        return over;
    }
}
