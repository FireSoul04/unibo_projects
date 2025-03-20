package a06.e2;

import javax.swing.*;
import java.util.*;
import java.awt.*;
import java.awt.event.ActionListener;

public class GUI extends JFrame {
    
    private static final long serialVersionUID = -6218820567019985015L;
    private final Map<JButton, Position> cells = new HashMap<>();
    private final Logic logic;
    
    public GUI(int size) {
        this.setDefaultCloseOperation(EXIT_ON_CLOSE);
        this.setSize(70*size, 70*size);
        logic = new LogicImpl(size);

        JPanel panel = new JPanel(new GridLayout(size,size));
        this.getContentPane().add(panel);
        
        ActionListener al = e -> {
            var jb = (JButton)e.getSource();
            var res = logic.click(cells.get(jb));
            for (var c1 : cells.keySet()) {
                if (c1.isEnabled()) {
                    c1.setText("");
                }
            }
            for (var c1 : cells.entrySet()) {
                for (var c2 : logic.flippedCards().entrySet()) {
                    if (c1.getValue().equals(c2.getKey())) {
                        c1.getKey().setText(Integer.toString(c2.getValue()));
                    }
                }
            }
            if (res != null) {
                for (var t : cells.entrySet()) {
                    if (t.getValue().equals(res.getX()) || t.getValue().equals(res.getY())) {
                        t.getKey().setEnabled(false);
                    }
                }
            }
            if (logic.isOver()) {
                for (var t : cells.keySet()) {
                    t.setEnabled(false);
                }
            }
        };
                
        for (int i=0; i<size; i++){
            for (int j=0; j<size; j++){
            	var pos = new Position(j,i);
                final JButton jb = new JButton();
                this.cells.put(jb, pos);
                jb.addActionListener(al);
                panel.add(jb);
            }
        }
        this.setVisible(true);
    }
    
}
