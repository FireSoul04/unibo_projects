package a06.e2;

import java.util.*;
import java.util.function.Function;
import java.util.stream.Collectors;

public class LogicImpl implements Logic {

    private final Random rand = new Random();
    private final int size;
    private final Map<Position, Integer> cards = new HashMap<>();
    private final Set<Position> selectedCards = new HashSet<>();

    public LogicImpl(int size) {
        this.size = size;
        setCards();
    }

    private void setCards() {
        for (int y = 0; y < size; y++) {
            for (int x = 0; x < size; x++) {
                cards.put(new Position(x, y), rand.nextInt(1, 7));
            }
        }
    }

    @Override
    public Pair<Position, Position> click(Position p) {
        selectedCards.add(p);
        if (selectedCards.size() == 2) {
            if (areCardsEqual()) {
                List<Position> l = new ArrayList<>(selectedCards);
                return new Pair<Position,Position>(l.get(0), l.get(1));
            }
        }
        return null;
    }

    private boolean areCardsEqual() {
        List<Position> l = new ArrayList<>(selectedCards);
        return cards.get(l.get(0)) == cards.get(l.get(1));
    }

    @Override
    public Map<Position, Integer> flippedCards() {
        return Collections.unmodifiableMap(selectedCards.stream().collect(Collectors.toMap(Function.identity(), t -> cards.get(t))));
    }

    @Override
    public boolean isOver() {
        if (selectedCards.size() == 2) {
            if (areCardsEqual()) {
                List<Position> l = new ArrayList<>(selectedCards);
                cards.remove(l.get(0));
                cards.remove(l.get(1));
            }
            selectedCards.clear();
        }
        boolean anyMatch = false;
        for (var c1 : cards.entrySet()) {
            for (var c2 : cards.entrySet()) {
                if (
                    !c1.getKey().equals(c2.getKey()) &&
                    c1.getValue() == c2.getValue()
                ) {
                    anyMatch = true;
                }
            }
        }
        return !anyMatch;
    }

}
