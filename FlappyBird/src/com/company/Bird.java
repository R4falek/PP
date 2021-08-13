package com.company;

import java.awt.*;

public class Bird {
    int y = Main.height/2;
    int x = 100;
    int size = 40;
    double velocity = 0;
    double gravity = 0.8;
    int lift = -20;
    int score = 0;
    double fitness = 0;
    NeuralNetwork brain;

    Bird(NeuralNetwork brain, boolean mutation){
        if(brain != null) {
            this.brain = new NeuralNetwork(brain);
            if(mutation) this.brain.mutate();
        }
        else this.brain = new NeuralNetwork(5, 8, 2);
        //System.out.println(this.brain);
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

        double[] inputs = new double[5];

        inputs[0] = (double) closest.x/Main.width;
        inputs[1] = (double) closest.y/Main.height;
        inputs[2] = (double) (closest.y + closest.hole)/Main.height;
        inputs[3] = (double) y/Main.height;
        inputs[4] = velocity/20;

        double[] action = brain.predict(inputs);

        if (action[1] > action[0]) up();
    }

    public Bird copy(){ return new Bird(brain, false); }

    public void up(){ velocity += lift; }

    public void update(){
        velocity += gravity;
        velocity = velocity < 15 ? velocity : 15;
        velocity = velocity > -20 ? velocity : -20;
        y += velocity;
        y = Math.min(y, Main.height - size / 2);

        score++;
    }

    public void paint(Graphics g2D){
        g2D.setColor(new Color(100, 149, 237, 100));
        g2D.fillOval(x, y, size, size);
        g2D.setColor(Color.WHITE);
        g2D.drawOval(x, y, size, size);
    }

    public boolean hit(int _x, int _y, int _z, int hole){ return ((y <= _y || y + size >= _y + hole) && x + size/2 == _x + _z / 2) || y >= Main.height - size / 2; }
}

