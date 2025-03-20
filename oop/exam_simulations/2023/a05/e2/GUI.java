package a05.e2;

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

            if (logic.click(cells.get(jb))) {
                for (var cell : cells.entrySet()) {
                    if (cell.getValue().equals(logic.getPlayer().position())) {
                        cell.getKey().setText("P");
                    } else if (cell.getValue().equals(logic.getEnemy().position())) {
                        cell.getKey().setText("E");
                    } else {
                        cell.getKey().setText("");
                    }
                }
            }
            if (logic.isOver()) {
                for (var cell : cells.keySet()) {
                    cell.setEnabled(false);
                }
            }
        };

        for (int i=0; i<size; i++){
            for (int j=0; j<size; j++){
            	var pos = new Position(j, i);
                final JButton jb = new JButton();
                this.cells.put(jb, pos);
                if (logic.getPlayer().position().equals(pos)) {
                    jb.setText("P");
                }
                if (logic.getEnemy().position().equals(pos)) {
                    jb.setText("E");
                }
                jb.addActionListener(al);
                panel.add(jb);
            }
        }
        this.setVisible(true);
    }
    
}
