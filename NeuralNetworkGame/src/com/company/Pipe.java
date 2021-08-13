package com.company;

import java.awt.*;

public class Pipe {
    int x;
    int y;
    int z = 10;
    static int hole = 60;
    int speed = -5;
    int gap = 400;

    Pipe(int i) {
        y = (int) (Math.random() * (Main.height - hole));
        x = i + gap + z;
        if(i == Main.width) x = Main.width + z;
    }

    public void update() { x+=speed; }

    public void paint(Graphics g2D) {
        g2D.setColor(Color.gray);
        g2D.fillRect(x, 0, z, y);
        g2D.fillRect(x, y + hole, z, Main.height);
    }
}
