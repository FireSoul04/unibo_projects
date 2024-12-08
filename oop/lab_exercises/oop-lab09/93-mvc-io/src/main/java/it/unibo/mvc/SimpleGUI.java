package it.unibo.mvc;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JTextArea;
import javax.swing.JTextField;

/**
 * A very simple program using a graphical interface.
 * 
 */
public final class SimpleGUI {

    private static final String TITLE = "My first java graphical interface";
    private static final int PROPORTION = 3;
    private final JFrame frame = new JFrame();
    /**
     * Create a simple GUI for printing to a file and visualize all the prints done.
     * @param title of window
     * @param controller for IO
     */
    public SimpleGUI(final String title, final Controller controller) {
        this.resize();
        this.frame.setTitle(title);
        this.frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        final JPanel panel = new JPanel(new BorderLayout());
        final JPanel buttonsPanel = new JPanel(new BorderLayout());
        final JTextField textField = new JTextField();
        final JTextArea textArea = new JTextArea();
        final JButton print = new JButton("Print");
        final JButton getHistory = new JButton("Show history");
        print.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(final ActionEvent e) {
                controller.setNextPrintedString(textField.getText());
                controller.printCurrentString();
            }
        });
        getHistory.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(final ActionEvent e) {
                String history = "";
                for (final String line : controller.getHistoryOfPrintedStrings()) {
                    history = history.concat(line).concat("\n");
                }
                textArea.setText(history);
            }
        });
        textArea.setEditable(false);
        buttonsPanel.add(print, BorderLayout.WEST);
        buttonsPanel.add(getHistory, BorderLayout.EAST);
        panel.add(textField, BorderLayout.NORTH);
        panel.add(textArea, BorderLayout.CENTER);
        panel.add(buttonsPanel, BorderLayout.SOUTH);
        this.frame.setContentPane(panel);
        this.frame.setVisible(true);
    }

    private void resize() {
        final Dimension screen = Toolkit.getDefaultToolkit().getScreenSize();
        final int sw = (int) screen.getWidth();
        final int sh = (int) screen.getHeight();
        frame.setSize(sw / PROPORTION, sh / PROPORTION);
    }

    /**
     * Main function.
     * @param args
     */
    public static void main(final String[] args) {
        new SimpleGUI(TITLE, new SimpleController(System.out));
    }
}
