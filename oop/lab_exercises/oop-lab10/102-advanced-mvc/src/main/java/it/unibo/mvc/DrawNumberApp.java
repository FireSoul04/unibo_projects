package it.unibo.mvc;

import java.io.FileNotFoundException;
import java.util.Arrays;
import java.util.List;

/**
 * 
 */
public final class DrawNumberApp implements DrawNumberViewObserver {
    
    private static final String CONFIGURATION_FILE = "src/main/resources/config.yml";
    private static final String LOGGER_FILE = "src/main/resources/info.log";

    private final DrawNumber model;
    private final List<DrawNumberView> views;

    /**
     * @param views
     *            the views to attach
     */
    public DrawNumberApp(final DrawNumberView... views) {
        /*
         * Side-effect proof
         */
        this.views = Arrays.asList(Arrays.copyOf(views, views.length));
        for (final DrawNumberView view: views) {
            view.setObserver(this);
            view.start();
        }
        final ConfigFileParser parsedConfig = new ConfigFileParser(CONFIGURATION_FILE);
        final int min = Integer.valueOf(parsedConfig.get("minimum"));
        final int max = Integer.valueOf(parsedConfig.get("maximum"));
        final int attempts = Integer.valueOf(parsedConfig.get("attempts"));
        this.model = new DrawNumberImpl(min, max, attempts);
    }

    @Override
    public void newAttempt(final int n) {
        try {
            final DrawResult result = model.attempt(n);
            for (final DrawNumberView view: views) {
                view.result(result);
            }
        } catch (IllegalArgumentException e) {
            for (final DrawNumberView view: views) {
                view.numberIncorrect();
            }
        }
    }

    @Override
    public void resetGame() {
        this.model.reset();
    }

    @Override
    public void quit() {
        /*
         * A bit harsh. A good application should configure the graphics to exit by
         * natural termination when closing is hit. To do things more cleanly, attention
         * should be paid to alive threads, as the application would continue to persist
         * until the last thread terminates.
         */
        System.exit(0);
    }

    /**
     * @param args
     *            ignored
     * @throws FileNotFoundException 
     */
    public static void main(final String... args) throws FileNotFoundException {
        final DrawNumberView swingView1 = new DrawNumberViewImpl();
        final DrawNumberView swingView2 = new DrawNumberViewImpl();
        final PrintStreamView fileLogger = new PrintStreamView(LOGGER_FILE);
        final PrintStreamView standardOut = new PrintStreamView(System.out);

        new DrawNumberApp(
            swingView1,
            swingView2,
            fileLogger,
            standardOut
        );
    }

}
