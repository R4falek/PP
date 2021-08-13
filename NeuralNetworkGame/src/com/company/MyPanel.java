package com.company;

import javax.swing.*;
import java.awt.*;
import java.util.ArrayList;

public class MyPanel extends JPanel {
    final int PANEL_WIDTH = Main.width;
    final int PANEL_HEIGHT = Main.height;
    int population = 500;
    int score = 0;
    int bestScore = 0;

    ArrayList<Bird> birds;
    ArrayList<Bird> savedBirds;
    Pipes pipes;

    public MyPanel(){
        this.setPreferredSize(new Dimension(PANEL_WIDTH,PANEL_HEIGHT));
        this.setBackground(Color.black);

        birds = new ArrayList<>();
        for (int i = 0 ; i < population ; i++) birds.add(new Bird(null, false));

        pipes = new Pipes();
        savedBirds = new ArrayList<>();
    }

    public void paint(Graphics g) {
        super.paint(g);
        Graphics2D g2D = (Graphics2D) g;

        pipes.paint(g2D);
        for(Bird bird : birds) bird.paint(g2D);

        g2D.setColor(Color.WHITE);
        g2D.drawString(String.valueOf(score), 10, 10);
    }
}
