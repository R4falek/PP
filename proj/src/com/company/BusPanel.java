package com.company;

import java.awt.*;

public class BusPanel {
    final int PANEL_WIDTH = 140;
    final int PANEL_HEIGHT = 70;
    final int PANEL_X = 10;
    final int PANEL_Y = 90;

    public BusPanel(){}

    public void paint(Graphics g2D, int chosenId, String chosenRoute){
        if(chosenId == -1) return;
        g2D.setColor(new Color(190, 130, 230, 200));
        g2D.fillRect(PANEL_X, PANEL_Y,PANEL_WIDTH, PANEL_HEIGHT);
        g2D.setColor(Color.white);
        g2D.setFont(new Font("Arial", Font.PLAIN, 20));
        g2D.drawString(chosenId+" "+chosenRoute, 20, 115);
    }
}
