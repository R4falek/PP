package com.company;

import java.awt.*;

public class MenuPanel {
    final int PANEL_WIDTH = 140;
    final int PANEL_HEIGHT = 70;
    final int PANEL_X = 10;
    final int PANEL_Y = 10;
    boolean buses = true;
    boolean stops = true;

    public MenuPanel(){}

    public void paint(Graphics g2D){
        g2D.setColor(new Color(190, 130, 230, 200));
        g2D.fillRect(PANEL_X, PANEL_Y,PANEL_WIDTH, PANEL_HEIGHT);

        g2D.setColor(Color.white);
        g2D.drawOval(20,20,16,16);
        g2D.setFont(new Font("Arial", Font.PLAIN, 20));
        g2D.drawString("Buses", 50, 35);
        if(buses)
            g2D.fillOval(25,25,6,6);

        g2D.setColor(Color.white);
        g2D.drawOval(20,50,16,16);
        g2D.setFont(new Font("Arial", Font.PLAIN, 20));
        g2D.drawString("Bus stops", 50, 65);
        if(stops)
            g2D.fillOval(25,55,6,6);
    }

    public String onWhatIsMouse(int x, int y){
        if(x > 20 && x < 36 && y > 20 && y < 36) return "buses";
        if(x > 20 && x < 36 && y > 50 && y < 66) return "stops";
        return null;
    }

    public void radioButtonsHandling(int x, int y){
        if(onWhatIsMouse(x, y) == "buses") buses = !buses;
        if(onWhatIsMouse(x, y) == "stops") stops = !stops;
    }
}
