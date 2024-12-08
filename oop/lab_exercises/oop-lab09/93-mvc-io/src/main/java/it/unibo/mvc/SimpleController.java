package it.unibo.mvc;

import java.io.PrintStream;
import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

/**
 * Creates a controller that write to a selectable file.
 */
public final class SimpleController implements Controller {

    private final PrintStream printStream;
    private final List<String> history;
    private String currentString;

    /**
     * Create a simple controller.
     * @param printStream
     */
    public SimpleController(final PrintStream printStream) {
        this.printStream = new PrintStream(printStream, false, StandardCharsets.UTF_8);
        this.history = new ArrayList<>();
        this.currentString = "";
    }

    /**
     * {@inheritDoc}
     */
    @Override
    public void setNextPrintedString(final String line) {
        this.currentString = Objects.requireNonNull(line);
        this.history.add(line);
    }

    /**
     * {@inheritDoc}
     */
    @Override
    public String getNextPrintedString() {
        return this.currentString;
    }

    /**
     * {@inheritDoc}
     */
    @Override
    public List<String> getHistoryOfPrintedStrings() {
        return List.copyOf(this.history);
    }

    /**
     * {@inheritDoc}
     */
    @Override
    public void printCurrentString() {
        if (this.currentString.isBlank()) {
            throw new IllegalStateException("String cannot be blank");
        }
        this.printStream.println(this.currentString);
    }
}
