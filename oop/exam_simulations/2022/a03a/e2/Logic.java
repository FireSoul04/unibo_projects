package a03a.e2;

public interface Logic {

    boolean click(Position p);

    Position player();

    Position computer();

    boolean doRestart();

    void restart();
}
