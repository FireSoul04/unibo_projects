package a04.e2;

import java.util.*;

public class LogicImpl implements Logic {

    private final List<Position> directions = List.of(
        new Position(-1, 0),
        new Position(-1, 1),
        new Position(0, 1),
        new Position(1, 1),
        new Position(1, 0),
        new Position(1, -1),
        new Position(0, -1),
        new Position(1, -1)
    );
    private final Random rand = new Random();
    private final int size;
    private Position rook;
    private Position king;

    public LogicImpl(final int size) {
        this.size = size;
        this.rook = this.getRandomPosition();
        do {
            this.king = this.getRandomPosition();
        } while (this.rook.equals(this.king));
    }

    @Override
    public boolean click(final Position p) {
        if (this.validRookPosition(p) && this.dontGoOverKing(p)) {
            this.rook = p;
            if (this.rook.equals(this.king)) {
                System.out.println("Vince");
            } else {
                this.moveKing();
            }
            return true;
        }
        return false;
    }

    private boolean validRookPosition(final Position p) {
        return !this.rook.equals(p)
            && (this.rook.x() == p.x() || this.rook.y() == p.y());
    }

    private boolean dontGoOverKing(final Position p) {
        if (this.sameRow()) {
            return Math.abs(this.rook.x() - p.x()) <= Math.abs(this.king.x() - this.rook.x());
        } else if (this.sameColumn()) {
            return Math.abs(this.rook.y() - p.y()) <= Math.abs(this.king.y() - this.rook.y());
        }
        return true;
    }

    private boolean sameRow() {
        return this.rook.y() == this.king.y();
    }

    private boolean sameColumn() {
        return this.rook.x() == this.king.x();
    }

    private void moveKing() {
        if (!this.isRookClose()) {
            Position nextPos;
            do {
                nextPos = this.getRandomDirection();
            } while (this.isOutOfBounds(this.king.sum(nextPos)));
            this.king = this.king.sum(nextPos);
        } else {
            this.king = this.rook;
        }
    }

    private boolean isRookClose() {
        return Math.abs(this.king.x() - this.rook.x()) <= 1 && Math.abs(this.king.y() - this.rook.y()) <= 1;
    }

    private Position getRandomDirection() {
        return this.directions.get(this.rand.nextInt(this.directions.size()));
    }

    private Position getRandomPosition() {
        return new Position(this.rand.nextInt(this.size), this.rand.nextInt(this.size));
    }

    private boolean isOutOfBounds(final Position p) {
        return p.x() < 0 || p.x() >= this.size || p.y() < 0 || p.y() >= this.size;
    }

    @Override
    public Position rook() {
        return this.rook;
    }

    @Override
    public Position king() {
        return this.king;
    }

    @Override
    public boolean quit() {
        return this.rook.equals(this.king);
    }

}
