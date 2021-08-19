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
    JButton button;

    boolean onlyBest = false;
    int key = 0;

    MyFrame(){
        slider = new MySlider(1, 500, 1, Main.width - 220, 10, 200, 20);
        this.add(slider);

        button = new JButton("Best bird");
        button.setBounds(10, 10, 90, 20);
        button.addActionListener(this);
        this.add(button);

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

        ga = new Ga(panel.population, 10);
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

            if(e.getSource() == button) {
                onlyBest = !onlyBest;
                ga.saveBest(panel.birds);
                panel.pipes.restart();
                panel.birds.clear();
            }

            if(panel.birds.size() == 0){
                if(panel.score > panel.bestScore) panel.bestScore = panel.score;
                System.out.println("Best score: "+panel.bestScore+" Score: "+panel.score);
                panel.score = 0;
                if(!onlyBest)
                    if(panel.savedBirds.size() == 0) {
                        panel.birds.add(new Bird(ga.bestBirdBrain, false));
                        for (int j = 0 ; j < panel.population - 1 ; j++) panel.birds.add(new Bird(null, false));
                    }
                    else panel.birds = ga.nextGeneration(panel.savedBirds);
                else panel.birds.add(new Bird(ga.bestBirdBrain, false));
                panel.savedBirds.clear();
                panel.pipes.restart();
            }

            repaint();
        }
    }

    @Override
    public void keyPressed(KeyEvent e) {
        if (panel.tap){ for(Bird bird : panel.birds) bird.up(); panel.tap = false; }
        key = e.getKeyCode();
    }

    @Override
    public void keyTyped(KeyEvent e) { }

    @Override
    public void keyReleased(KeyEvent e) { panel.tap = true; key = 0; }
}

class MySlider extends JSlider {
    MySlider(int min, int max, int val, int x, int y, int width, int height){
        setMinimum(min);
        setMaximum(max);
        setValue(val);
        setBounds(x, y, width, height);
    }
}
