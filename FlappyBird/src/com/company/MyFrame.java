package com.company;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

public class MyFrame extends JFrame implements KeyListener, ActionListener {

    MyPanel panel;
    JSlider slider;
    Timer timer;
    Ga ga;

    int x = 0;

    MyFrame(){
        slider = new MySlider(1, 500, 1, Main.width - 220, 10, 200, 20);
        this.add(slider);

        panel = new MyPanel();
        this.add(panel);
        this.pack();

        this.setTitle("FlappyBird");
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setVisible(true);

        setFocusable(true);
        addKeyListener(this);
        setFocusTraversalKeysEnabled(false);

        timer = new Timer(10, this);
        timer.start();

        ga = new Ga(panel.population);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        for(int i = 0 ; i < slider.getValue() ; i++){
            //if(x == 24){ x = 0; panel.bird.up();} x++;
            for(Bird bird : panel.birds){
                bird.think(panel.pipes);
                bird.update();
                if(panel.pipes.hitCheck(bird)) panel.savedBirds.add(bird);
            }
            for(Bird bird : panel.savedBirds) panel.birds.remove(bird);

            panel.pipes.update();
            panel.score++;

            if(panel.birds.size() == 0){
                if(panel.score > panel.bestScore) panel.bestScore = panel.score;
                System.out.println("Best score: "+panel.bestScore+" Score: "+panel.score);
                panel.score = 0;
                panel.birds = ga.nextGeneration(panel.savedBirds);
                panel.savedBirds.clear();
                panel.pipes.restart();
            }

            repaint();
        }
    }

    @Override
    public void keyPressed(KeyEvent e) { if (panel.tap){ for(Bird bird : panel.birds) bird.up(); panel.tap = false; } }

    @Override
    public void keyTyped(KeyEvent e) { }

    @Override
    public void keyReleased(KeyEvent e) { panel.tap = true; }
}

class MySlider extends JSlider {
    MySlider(int min, int max, int val, int x, int y, int width, int height){
        setMinimum(min);
        setMaximum(max);
        setValue(val);
        setBounds(x, y, width, height);
    }
}
