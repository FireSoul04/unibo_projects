package it.unibo.mvc;

import java.lang.reflect.InvocationTargetException;
import java.util.ArrayList;
import java.util.List;

import it.unibo.mvc.api.DrawNumberController;
import it.unibo.mvc.api.DrawNumberView;
import it.unibo.mvc.controller.DrawNumberControllerImpl;
import it.unibo.mvc.model.DrawNumberImpl;

/**
 * Application entry-point.
 */
public final class LaunchApp {

    private static final int VIEWS_PER_CLASS = 3;

    private LaunchApp() { }

    /**
     * Runs the application.
     *
     * @param args ignored
     * @throws ClassNotFoundException if the fetches class does not exist
     * @throws NoSuchMethodException if the 0-ary constructor do not exist
     * @throws InvocationTargetException if the constructor throws exceptions
     * @throws InstantiationException if the constructor throws exceptions
     * @throws IllegalAccessException in case of reflection issues
     * @throws IllegalArgumentException in case of reflection issues
     */
    @SuppressWarnings("unchecked")
    public static void main(final String... args) throws Exception {
        final var model = new DrawNumberImpl();
        final DrawNumberController app = new DrawNumberControllerImpl(model);
        final List<Class<DrawNumberView>> drawClasses = new ArrayList<>();
        drawClasses.add((Class<DrawNumberView>)Class.forName("it.unibo.mvc.view.DrawNumberSwingView"));
        drawClasses.add((Class<DrawNumberView>)Class.forName("it.unibo.mvc.view.DrawNumberConsoleView"));

        for (final var drawClass : drawClasses) {
            for (int i = 0; i < LaunchApp.VIEWS_PER_CLASS; i++) {
                app.addView(drawClass.getConstructor().newInstance());
            }
        }
    }
}
