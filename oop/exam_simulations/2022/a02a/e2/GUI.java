package a02a.e2;

import javax.swing.*;
import java.util.*;
import java.awt.*;
import java.awt.event.*;

public class GUI extends JFrame {
    
    private final Map<JButton, Position> cells = new HashMap<>();
    private final Logic logic;
    
    public GUI(int size) {
        this.setDefaultCloseOperation(EXIT_ON_CLOSE);
        this.setSize(100*size, 100*size);
        this.logic = new LogicImpl(size);
        
        JPanel panel = new JPanel(new GridLayout(size,size));
        this.getContentPane().add(panel);
        
        ActionListener al = new ActionListener(){
            public void actionPerformed(ActionEvent e){
        	    var button = (JButton)e.getSource();
                final var disabled = logic.click(cells.get(button));
                button.setText("B");
                disabled.forEach(t -> cells.entrySet().stream().filter(v -> v.getValue().equals(t)).forEach(v -> v.getKey().setEnabled(false)));
                if (logic.restart()) {
                    cells.forEach((k, v) -> {
                        k.setEnabled(true);
                        k.setText("");
                    });
                }
            }
        };
                
        for (int i=0; i<size; i++){
            for (int j=0; j<size; j++){
                final Position p = new Position(j, i);
                final JButton jb = new JButton(" ");
                this.cells.put(jb, p);
                jb.addActionListener(al);
                panel.add(jb);
            }
        }
        this.setVisible(true);
    }    
}
