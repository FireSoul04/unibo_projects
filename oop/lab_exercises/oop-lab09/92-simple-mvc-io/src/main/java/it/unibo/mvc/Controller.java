package it.unibo.mvc;

import java.io.File;
import java.io.IOException;
import java.io.PrintStream;
import java.nio.charset.StandardCharsets;

/**
 * Application controller. Performs the I/O.
 */
public class Controller {

    private static final String DEFAULT_FILE_NAME = "output.txt";
    private static final String DEFAULT_PATH = System.getProperty("user.home")
        + File.separator + DEFAULT_FILE_NAME;

    private File file;

    /**
     * Create a controller with default file path.
     */
    public Controller() {
        this.file = new File(DEFAULT_PATH);
    }

    /**
     * Set the new file to work on.
     * 
     * @param file file to work on
     */
    public void setCurrentFile(final File file) {
        this.file = file;
    }

    /**
     * Gives the current file in use.
     * @return file in use
     */
    public File getCurrentFile() {
        return this.file;
    }

    /**
     * Gives the absolute path of current file in use.
     * @return path of file in use
     */
    public String getCurrentFilePath() {
        return this.file.getAbsolutePath();
    }

    /**
     * Write to the file attached to this controller.
     * @param line to write inside the file
     * @throws IOException if file is not readable
     */
    public void writeToCurrentFile(final String line) throws IOException {
        try (PrintStream ps = new PrintStream(file, StandardCharsets.UTF_8)) {
            ps.write(line.getBytes(StandardCharsets.UTF_8));
        } catch (final IOException e) {
            e.printStackTrace(); // NOPMD: allowed as this is just an exercise
        }
    }
}
