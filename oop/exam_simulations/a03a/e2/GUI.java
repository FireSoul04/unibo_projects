package a03a.e2;

import javax.swing.*;
import java.util.*;
import java.awt.*;
import java.awt.event.ActionListener;

public class GUI extends JFrame {
    
    private static final long serialVersionUID = -6218820567019985015L;
    private final Map<JButton, Point> cells = new HashMap<>();
    private final Logic logic;
    
    public GUI(int width, int height) {
        logic = new LogicImpl(width, height);
        this.setDefaultCloseOperation(EXIT_ON_CLOSE);
        this.setSize(70*width, 70*height);
        
        JPanel panel = new JPanel(new GridLayout(height,width));
        this.getContentPane().add(panel);
        
        ActionListener al = e -> {
            var jb = (JButton)e.getSource();
            cells.keySet().forEach(t -> t.setText(""));
            for (final var entry : cells.entrySet()) {
                if (entry.getValue().equals(logic.target())) {
                    entry.getKey().setText("o");
                }
            }
            final var trace = logic.click(cells.get(jb));
            cells.entrySet().forEach(t -> trace.stream().filter(p -> t.getValue().equals(p)).forEach(p -> t.getKey().setText("*")));
            if (logic.quit()) {
                System.exit(0);
            }
        };
                
        for (int i=0; i<height; i++){
            for (int j=0; j<width; j++){
            	var pos = new Point(j, i);
                final JButton jb = new JButton();
                if (pos.equals(logic.target())) {
                    jb.setText("o");
                }
                this.cells.put(jb, pos);
                jb.addActionListener(al);
                panel.add(jb);
            }
        }
        this.setVisible(true);
    }
    
}
