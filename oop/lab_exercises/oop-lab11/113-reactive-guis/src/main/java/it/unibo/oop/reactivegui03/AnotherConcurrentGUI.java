package it.unibo.oop.reactivegui03;

import java.awt.Dimension;
import java.awt.Toolkit;
import java.lang.reflect.InvocationTargetException;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.SwingUtilities;

/**
 * Third experiment with reactive gui.
 */
@SuppressWarnings("PMD.AvoidPrintStackTrace")
public final class AnotherConcurrentGUI extends JFrame {
    
    private static final long serialVersionUID = 1L;
    private static final double WIDTH_PERC = 0.2;
    private static final double HEIGHT_PERC = 0.1;
    private final JLabel display = new JLabel();
    private final JButton up = new JButton("up");
    private final JButton down = new JButton("down");
    private final JButton stop = new JButton("stop");

    /**
     * Builds a new CGUI.
     */
    public AnotherConcurrentGUI() {
        super();
        final Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
        this.setSize((int) (screenSize.getWidth() * WIDTH_PERC), (int) (screenSize.getHeight() * HEIGHT_PERC));
        this.setDefaultCloseOperation(EXIT_ON_CLOSE);
        final JPanel panel = new JPanel();
        panel.add(display);
        panel.add(up);
        panel.add(down);
        panel.add(stop);
        this.getContentPane().add(panel);
        this.setVisible(true);
        /*
         * Create the counter agent and start it. This is actually not so good:
         * thread management should be left to
         * java.util.concurrent.ExecutorService
         */
        final CounterAgent counterAgent = new CounterAgent();
        final StopAfterDelayAgent stopAgent = new StopAfterDelayAgent(counterAgent);
        new Thread(counterAgent).start();
        new Thread(stopAgent).start();
        /*
         * Register a listener that stops it
         */
        up.addActionListener(e -> counterAgent.goUp());
        down.addActionListener(e -> counterAgent.goDown());
        stop.addActionListener(e -> counterAgent.stopCounting());
    }

    /*
     * The counter agent is implemented as a nested class. This makes it
     * invisible outside and encapsulated.
     */
    private class CounterAgent implements Runnable {
        /*
         * Stop is volatile to ensure visibility. Look at:
         * 
         * http://archive.is/9PU5N - Sections 17.3 and 17.4
         * 
         * For more details on how to use volatile:
         * 
         * http://archive.is/4lsKW
         * 
         */
        private volatile boolean stop;
        private volatile int sign = 1;
        private int counter;

        @Override
        public void run() {
            while (!this.stop) {
                try {
                    // The EDT doesn't access `counter` anymore, it doesn't need to be volatile 
                    final var nextText = Integer.toString(this.counter);
                    SwingUtilities.invokeAndWait(() -> AnotherConcurrentGUI.this.display.setText(nextText));
                    this.counter = this.counter + this.sign;
                    Thread.sleep(100);
                } catch (InvocationTargetException | InterruptedException ex) {
                    /*
                     * This is just a stack trace print, in a real program there
                     * should be some logging and decent error reporting
                     */
                    ex.printStackTrace();
                }
            }
        }

        /**
         * External command to stop counting.
         */
        public synchronized void stopCounting() {
            this.stop = true;
        }

        /**
         * 
         */
        public synchronized void goUp() {
            this.sign = 1;
        }

        /**
         * 
         */
        public synchronized void goDown() {
            this.sign = -1;
        }
    }

    /*
     * The counter agent is implemented as a nested class. This makes it
     * invisible outside and encapsulated.
     */
    private class StopAfterDelayAgent implements Runnable {

        private final CounterAgent counterAgent;

        public StopAfterDelayAgent(final CounterAgent counterAgent) {
            this.counterAgent = counterAgent;
        }

        @Override
        public void run() {
            try {
                Thread.sleep(10 * 1000);
                this.counterAgent.stopCounting();
                AnotherConcurrentGUI.this.up.setEnabled(false);
                AnotherConcurrentGUI.this.down.setEnabled(false);
                AnotherConcurrentGUI.this.stop.setEnabled(false);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}
