package com.company;

import java.awt.*;
import java.awt.event.KeyEvent;

public class Bird {
    int y = Main.height/2;
    int x = 100;
    int size = 40;
    double velocity = 10;
    int score = 0;
    double fitness = 0;
    NeuralNetwork brain;

    public Bird(NeuralNetwork brain, boolean mutation){
        if(brain != null) {
            this.brain = new NeuralNetwork(brain);
            if(mutation) this.brain.mutate();
        }
        else this.brain = new NeuralNetwork(4, 8, 2);
        this.brain.setLearningRate(0.2);
    }

    public void think(Pipes pipes){
        Pipe closest = null;
        int record = Main.width * 2;
        for (int i = 0; i < 3; i++) {
            int diff = pipes.pipes.get(i).x - this.x;
            if (diff > 0 && diff < record) {
                record = diff;
                closest = pipes.pipes.get(i);
            }
        }

        double[] inputs = new double[4];

        inputs[0] = (double) closest.x/Main.width;
        inputs[1] = (double) closest.y/Main.height;
        inputs[2] = (double) (closest.y + closest.hole)/Main.height;
        inputs[3] = (double) y/Main.height;

        double[] action = brain.predict(inputs);

        if (action[0] > 0.5) up();
        if (action[1] > 0.5) down();
    }

    public void paint(Graphics g2D){
        g2D.setColor(new Color(100, 149, 237, 100));
        g2D.fillOval(x, y, size, size);
        g2D.setColor(Color.WHITE);
        g2D.drawOval(x, y, size, size);
    }

    public void up() { y -= velocity; }

    public void down() { y += velocity; }

    public void left() { x -= velocity; if(x < 10) x = 10;}

    public void right() { x += velocity; if(x > 100) x = 100; }

    public void update(int key){
        if(key == KeyEvent.VK_W) up();
        if(key == KeyEvent.VK_S) down();
        score++;
    }

    public Bird copy(){ return new Bird(brain, false); }

    public boolean hit(int _x, int _y, int hole) { return ((x >= _x && (y <= _y || y + size >= _y + hole)) || y <= 0 || y + size >= Main.height); }
}
