package a04.e2;

import javax.swing.*;
import java.util.*;
import java.awt.*;
import java.awt.event.ActionListener;

public class GUI extends JFrame {
    
    private static final long serialVersionUID = -6218820567019985015L;
    private final Map<JButton, Point> cells = new HashMap<>();
    private final Logic logic;
    
    public GUI(int width) {
        logic = new LogicImpl(width);
        this.setDefaultCloseOperation(EXIT_ON_CLOSE);
        this.setSize(70*width, 70*width);
        
        JPanel panel = new JPanel(new GridLayout(width,width));
        this.getContentPane().add(panel);
        
        ActionListener al = e -> {
            var jb = (JButton)e.getSource();
            if (logic.click(cells.get(jb))) {
                jb.setText("*");
            }
            if (logic.quit()) {
                cells.keySet().forEach(t -> t.setEnabled(false));
            }
        };
                
        for (int i=0; i<width; i++){
            for (int j=0; j<width; j++){
            	var pos = new Point(j, i);
                final JButton jb = new JButton();
                if (pos.equals(logic.getStartingPoint())) {
                    jb.setText("*");
                }
                this.cells.put(jb, pos);
                jb.addActionListener(al);
                panel.add(jb);
            }
        }
        this.setVisible(true);
    }
    
}
