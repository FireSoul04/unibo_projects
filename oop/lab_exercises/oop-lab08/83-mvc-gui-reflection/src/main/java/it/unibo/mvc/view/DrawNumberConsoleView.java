package it.unibo.mvc.view;

import it.unibo.mvc.api.DrawNumberController;
import it.unibo.mvc.api.DrawNumberView;
import it.unibo.mvc.api.DrawResult;

public class DrawNumberConsoleView implements DrawNumberView {

    private static final String NEW_GAME = ": a new game starts!";

    @Override
    public void setController(final DrawNumberController observer) {
        
    }

    @Override
    public void start() {
        message("GUESS A NUMBER GAME");
    }

    @Override
    public void result(final DrawResult res) {
        switch (res) {
            case YOURS_HIGH, YOURS_LOW -> message(res.getDescription());
            case YOU_WON, YOU_LOST -> message(res.getDescription() + NEW_GAME);
            default -> throw new IllegalStateException("Unknown game state");
        }
    }

    private void message(final String msg) {
        System.out.println(msg);
    }

}
