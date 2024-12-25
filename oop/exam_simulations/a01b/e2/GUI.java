package a01b.e2;

import javax.swing.*;
import java.util.*;
import java.awt.*;
import java.awt.event.ActionListener;

import a01b.e2.Logic.Point;

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
            var num = logic.click(cells.get(jb));
            if (num > 0) {
                jb.setText(Integer.toString(num));
            }
            var clickedPoints = logic.getClickedPoints();
            System.out.println(clickedPoints);
            for (var entry : cells.entrySet()) {
                if (clickedPoints.contains(entry.getValue())) {
                    entry.getKey().setText(Integer.toString(clickedPoints.indexOf(entry.getValue()) + 1));
                } else {
                    entry.getKey().setText("");
                }
            }
            if (logic.quit()) {
                System.exit(0);
            }
        };
                
        for (int i=0; i<size; i++){
            for (int j=0; j<size; j++){
                final JButton jb = new JButton();
                this.cells.put(jb, new Point(j, i));
                jb.addActionListener(al);
                panel.add(jb);
            }
        }
        this.setVisible(true);
    }
    
}
