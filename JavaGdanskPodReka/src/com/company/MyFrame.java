package com.company;

import javax.swing.*;

public class MyFrame extends JFrame {

    MapPanel mapPanel;

    MyFrame() throws Exception {

        mapPanel = new MapPanel();

        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setTitle("Gdańsk pod ręką");
        this.add(mapPanel);
        this.pack();
        this.setLocationRelativeTo(null);
        this.setLayout(null);
        this.setVisible(true);
    }

}
