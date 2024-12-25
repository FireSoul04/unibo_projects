package a01a.e2;

import javax.swing.*;
import java.util.*;
import java.awt.*;
import java.awt.event.ActionListener;

import a01a.e2.Logic.Point;

public class GUI extends JFrame {
    
    private static final long serialVersionUID = -6218820567019985015L;
    private final Map<JButton, Point> cells = new HashMap<>();
    private final Logic logic;
    
    public GUI(int size) {
        this.logic = new LogicImpl(size);
        this.setDefaultCloseOperation(EXIT_ON_CLOSE);
        this.setSize(100*size, 100*size);
        
        JPanel panel = new JPanel(new GridLayout(size,size));
        this.getContentPane().add(panel);
        
        ActionListener al = e -> {
            var jb = (JButton)e.getSource();
            final var map = logic.click(cells.get(jb));
            for (final var entry : cells.entrySet()) {
                if (map.containsKey(entry.getValue())) {
                    final int num = map.get(entry.getValue());
                    entry.getKey().setText(num > 0 ? Integer.toString(num) : "");
                } else {
                    entry.getKey().setText("");
                }
            }
            if (logic.quit()) {
                System.exit(0);
            }
        };

        for (int y=0; y<size; y++){
            for (int x=0; x<size; x++){
                final JButton jb = new JButton("");
                this.cells.put(jb, new Point(x, y));
                jb.addActionListener(al);
                panel.add(jb);
            }
        }
        this.setVisible(true);
    }
    
}
