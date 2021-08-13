package com.company;

import java.awt.*;

public class Pipe {
    int x;
    int y;
    int z = 60;
    int hole = 160;
    int speed = -5;
    int gap = 500;

    Pipe(int i){
        y = (int) (Math.random() * (Main.height - hole - 50));
        x = gap + i + z;
        if(Main.width == i) x = Main.width + z;
    }

    public void paint(Graphics g2D){
        g2D.setColor(Color.gray);
        g2D.fillRect(x, 0, z, y);
        g2D.fillRect(x , y + hole, z, Main.height);
    }

    public void update(){ x += speed; }

}
