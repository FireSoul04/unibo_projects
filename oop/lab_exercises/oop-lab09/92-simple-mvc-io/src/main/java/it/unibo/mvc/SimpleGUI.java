package it.unibo.mvc;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JTextArea;

/**
 * A very simple program using a graphical interface.
 * 
 */
public final class SimpleGUI {

    private static final String TITLE = "My first java graphical interface";
    private static final int PROPORTION = 3;

    private final JFrame frame = new JFrame();

    /**
     * Create a simple GUI for saving a string into a file.
     * @param title of window
     * @param controller of IO
     */
    public SimpleGUI(final String title, final Controller controller) {
        this.resize();
        this.frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.frame.setTitle(title);
        this.frame.setLocationByPlatform(true);
        final JPanel panel = new JPanel(new BorderLayout());
        final JButton button = new JButton("Save");
        final JTextArea textArea = new JTextArea();
        button.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(final ActionEvent e) {
                try {
                    controller.writeToCurrentFile(textArea.getText());
                } catch (IOException ex) {
                    ex.printStackTrace(); // NOPMD: allowed as this is just an exercise
                }
            }
        });
        panel.add(button, BorderLayout.SOUTH);
        panel.add(textArea, BorderLayout.CENTER);
        this.frame.setContentPane(panel);
        this.frame.setVisible(true);
    }

    private void resize() {
        final Dimension screen = Toolkit.getDefaultToolkit().getScreenSize();
        final int sw = (int) screen.getWidth();
        final int sh = (int) screen.getHeight();
        this.frame.setSize(sw / PROPORTION, sh / PROPORTION);
    }

    /**
     * Create a SimpleGUI object.
     * @param args
     */
    public static void main(final String[] args) {
        new SimpleGUI(TITLE, new Controller());
    }
}
