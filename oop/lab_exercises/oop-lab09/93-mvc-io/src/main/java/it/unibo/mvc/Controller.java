package it.unibo.mvc;

import java.util.List;

/**
 * Creates a controller that write to a file.
 */
public interface Controller {

    /**
     * Set the string to be printed.
     * @param line new string to be printed
     * @throws NullPointerException if line is null
     */
    void setNextPrintedString(String line);

    /**
     * Get the string to be printed.
     * @return string to be printed
     */
    String getNextPrintedString();

    /**
     * Get the history of printed strings.
     * @return list of strings printed
     */
    List<String> getHistoryOfPrintedStrings();

    /**
     * Print to the stream the current string.
     * @throws IllegalStateException if the string to be printed is blank
     */
    void printCurrentString();
}
