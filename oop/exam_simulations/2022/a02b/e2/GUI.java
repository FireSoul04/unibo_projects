package a02b.e2;

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
        
        JPanel main = new JPanel(new BorderLayout());
        JPanel panel = new JPanel(new GridLayout(size,size));
        JButton check = new JButton("Check > Restart");
        this.getContentPane().add(main);
        main.add(BorderLayout.CENTER, panel);
        main.add(BorderLayout.SOUTH, check);
        
        ActionListener al = new ActionListener(){
            public void actionPerformed(ActionEvent e){
        	    var button = (JButton)e.getSource();
                button.setText(logic.click(cells.get(button)) ? "*" : "");
            }
        };
        check.addActionListener(e -> {
            final var disabledCells = logic.checkRestart();
            if (disabledCells == null) {
                restart();
            } else {
                disabledCells.forEach(t -> cells.entrySet().stream().filter(a -> a.getValue().equals(t)).forEach(a -> a.getKey().setEnabled(false)));
            }
        });
                
        for (int i=0; i<size; i++){
            for (int j=0; j<size; j++){
                final Position p = new Position(j, i);
                final JButton jb = new JButton();
                this.cells.put(jb, p);
                jb.addActionListener(al);
                panel.add(jb);
            }
        }
        this.setVisible(true);
    }

    private void restart() {
        cells.forEach((k, v) -> k.setEnabled(true));
        cells.forEach((k, v) -> k.setText(""));
    }
}
