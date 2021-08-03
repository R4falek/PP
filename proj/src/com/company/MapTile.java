package com.company;

import javax.swing.*;
import java.awt.*;

public class MapTile {
    int x;
    int y;
    Image tile;

    public MapTile(String tilePath, int _x, int _y){
        x = _x;
        y = _y;
        tile = new ImageIcon(tilePath).getImage();
    }
}
