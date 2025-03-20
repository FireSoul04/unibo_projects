package a03a.e2;

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
        	    var jb = (JButton)e.getSource();
                if (logic.click(cells.get(jb))) {
                    cells.forEach((k, v) -> {
                        if (v.equals(logic.player())) {
                            k.setText("*");
                        } else if (v.equals(logic.computer())) {
                            k.setText("o");
                        } else {
                            k.setText("");
                        }
                    });
                }
                if (logic.doRestart()) {
                    restart();
                }
            }
        };
                
        for (int i=0; i<size; i++){
            for (int j=0; j<size; j++){
                final Position pos = new Position(j, i);
                final JButton jb = new JButton();
                this.cells.put(jb, pos);
                if (pos.equals(logic.player())) {
                    jb.setText("*");
                } else if (pos.equals(logic.computer())) {
                    jb.setText("o");
                }
                jb.addActionListener(al);
                panel.add(jb);
            }
        }
        this.setVisible(true);
    }

    private void restart() {
        logic.restart();
        cells.forEach((k, v) -> {
            if (v.equals(logic.player())) {
                k.setText("*");
            } else if (v.equals(logic.computer())) {
                k.setText("o");
            } else {
                k.setText("");
            }
        });
    }
}
