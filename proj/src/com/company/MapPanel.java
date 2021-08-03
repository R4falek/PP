package com.company;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class MapPanel extends JPanel implements ActionListener, KeyListener, MouseListener {
    final int PANEL_WIDTH = 1020;
    final int PANEL_HEIGHT = 1080;
    Timer timer;
    int xVelocity = 0;
    int yVelocity = 0;
    int velocity = 40;

    Map map = new Map();
    Buses buses = new Buses();
    BusStops busStops = new BusStops();
    MenuPanel menuPanel = new MenuPanel();
    BusPanel busPanel = new BusPanel();

    int refresh = 0;

    MapPanel() throws Exception {
        this.setPreferredSize(new Dimension(PANEL_WIDTH,PANEL_HEIGHT));
        this.setBackground(Color.black);
        timer = new Timer(10, this);
        timer.start();
        addKeyListener(this);
        addMouseListener(this);
        setFocusable(true);
        setFocusTraversalKeysEnabled(false);
        setLayout(null);
    }

    public void paint(Graphics g) {
        super.paint(g);
        Graphics2D g2D = (Graphics2D) g;
        g2D.setFont(new Font("Arial", Font.PLAIN, 12));

        map.paint(g2D);
        g2D.setStroke(new BasicStroke(5));
        buses.paintPath(g2D, map.x, map.y, buses.chosenBusId);
        g2D.setStroke(new BasicStroke(1));
        busStops.paint(g2D, map.x, map.y, menuPanel.stops);         //PAINTING EVERYTHING
        buses.paint(g2D, map.x, map.y, menuPanel.buses);
        busStops.paintChosenBusStop(g2D, map.x, map.y);


        menuPanel.paint(g2D);
        busPanel.paint(g2D, buses.chosenBusId, buses.findLineById(buses.chosenBusId));   //PAINTING PANELS
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        map.x += xVelocity;
        map.y += yVelocity;

        if(refresh == 500){
            try { buses.refresh(); } catch (Exception exception) { exception.printStackTrace(); }   //REFRESH BUSES DATA
            refresh = 0;
        }
        refresh++;

        if(getMousePosition() != null){
            buses.setOnTop(buses.busIdWhichMouseIsOn(getMousePosition().x - map.x, getMousePosition().y - map.y, null), menuPanel.buses);  //SETTING BUSES ON TOP
            busStops.setOnTop(busStops.stopIdWhichMouseIsOn(getMousePosition().x - map.x, getMousePosition().y - map.y), menuPanel.stops);   //SETTING BUS STOPS ON TOP
        }
        repaint();
    }

    public void keyPressed(KeyEvent e){
        int c = e.getKeyCode();

        if (c == KeyEvent.VK_A)
            xVelocity = velocity;
        if (c == KeyEvent.VK_D)
            xVelocity = -velocity;
        if (c == KeyEvent.VK_S)
            yVelocity = -velocity;
        if (c == KeyEvent.VK_W)
            yVelocity = velocity;
    }

    public void keyTyped(KeyEvent e){}

    public void keyReleased(KeyEvent e){
        int c = e.getKeyCode();

        if (c == KeyEvent.VK_D || c == KeyEvent.VK_A)
            xVelocity = 0;
        if (c == KeyEvent.VK_S || c == KeyEvent.VK_W)
            yVelocity = 0;
    }

    @Override
    public void mouseClicked(MouseEvent e) {
        if(getMousePosition() != null){                                                                                                       //CHOOSING A BUS ID
            buses.chosenBusId = buses.busIdWhichMouseIsOn(getMousePosition().x - map.x, getMousePosition().y - map.y, menuPanel.onWhatIsMouse(getMousePosition().x, getMousePosition().y));
            try { buses.getBusPath(); } catch (Exception exception) { exception.printStackTrace(); }                                         //DOWNLOADING PATH
            busStops.chosenBusStop = busStops.stopIdWhichMouseIsOn(getMousePosition().x - map.x, getMousePosition().y - map.y);       //CHOOSING A BUS STOP
            menuPanel.radioButtonsHandling(getMousePosition().x, getMousePosition().y);                                                    //RADIO BUTTONS HANDLING
        }
    }

    @Override
    public void mousePressed(MouseEvent e) { }

    @Override
    public void mouseReleased(MouseEvent e) { }

    @Override
    public void mouseEntered(MouseEvent e) { }

    @Override
    public void mouseExited(MouseEvent e) { }
}