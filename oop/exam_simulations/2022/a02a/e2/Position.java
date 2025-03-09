package a02a.e2;

public record Position(int x, int y) {
    public Position sum(final Position p) {
        return new Position(x + p.x, y + p.y);
    }
}
