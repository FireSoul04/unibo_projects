package a03b.e2;

import javax.swing.*;

import a03b.e2.Logic.Player;

import java.util.*;
import java.awt.*;
import java.awt.event.*;

public class GUI extends JFrame {
    
    private final Map<JButton, Position> cells = new HashMap<>();
    private final Logic logic;
    
    public GUI(int size) {
        this.setDefaultCloseOperation(EXIT_ON_CLOSE);
        this.setSize(100*size, 100*size);
        logic = new LogicImpl(size);
        
        JPanel panel = new JPanel(new GridLayout(size,size));
        this.getContentPane().add(panel);
        
        ActionListener al = new ActionListener(){
            public void actionPerformed(ActionEvent e){
        	    var button = (JButton)e.getSource();
                logic.click(cells.get(button));
                cells.forEach((k, v) -> {
                    if (logic.pawns().containsKey(v)) {
                        k.setText(logic.pawns().get(v).equals(Player.HUMAN) ? "*" : "o");
                    } else {
                        k.setText("");
                    }
                });
                if (logic.doReset()) {
                    logic.reset();
                    cells.forEach((k, v) -> {
                        if (logic.pawns().containsKey(v)) {
                            k.setText(logic.pawns().get(v).equals(Player.HUMAN) ? "*" : "o");
                        } else {
                            k.setText("");
                        }
                    });
                }
            }
        };
        
        for (int i=0; i<size; i++){
            for (int j=0; j<size; j++){
                final Position pos = new Position(j, i);
                final JButton jb = new JButton();
                if (logic.pawns().containsKey(pos)) {
                    jb.setText(logic.pawns().get(pos).equals(Player.HUMAN) ? "*" : "o");
                }
                this.cells.put(jb, pos);
                jb.addActionListener(al);
                panel.add(jb);
            }
        }
        this.setVisible(true);
    }    
}
