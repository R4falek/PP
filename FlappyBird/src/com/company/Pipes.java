package com.company;

import java.awt.*;
import java.util.ArrayList;

public class Pipes {
    ArrayList<Pipe> pipes;

    Pipes(){
        pipes = new ArrayList<>();
        for (int i = 0 ; i < 10 ; i++) {
            if (i == 0) pipes.add(new Pipe(Main.width));
            else pipes.add(new Pipe(pipes.get(pipes.size()-1).x));
        }
    }

    public void removeAndAddNewOne(){
        if(pipes.get(0).x <= -pipes.get(0).z){
            pipes.remove(0);
            pipes.add(new Pipe(pipes.get(pipes.size()-1).x));
        }
    }

    public boolean hitCheck(Bird bird){
        //restart(bird);
        return bird.hit(pipes.get(0).x, pipes.get(0).y, pipes.get(0).z, pipes.get(0).hole);
    }

    public void paint(Graphics g2D){ for (int i = 0 ; i < 10 ; i++)pipes.get(i).paint(g2D); }

    public void update(){
        removeAndAddNewOne();
        for (int i = 0 ; i < 10 ; i++) pipes.get(i).update();
    }

    public void restart(){  //Bird bird){
        pipes.clear();
        for (int i = 0 ; i < 10 ; i++) {
            if (i == 0) pipes.add(new Pipe(Main.width));
            else pipes.add(new Pipe(pipes.get(pipes.size()-1).x));
        }
        //bird.y = Main.height/2;
        //bird.score = 0;
    }
}
