package com.company;

import java.awt.*;
import java.util.ArrayList;

public class Map {
    ArrayList<MapTile> mapTiles = new ArrayList<>();
    double scale;
    int x;
    int y;

    public Map(){
        scale = 0.3;
        x = 0;
        y = 0;
        setMap();
    }

    public void setMap(){
        MapTile LG = new MapTile("mapTiles/LG.jpg", -1398, -958);
        mapTiles.add(LG);
        MapTile PG = new MapTile("mapTiles/PG.jpg", 1398, -958);
        mapTiles.add(PG);
        MapTile GS = new MapTile("mapTiles/GS.jpg", 0, -958);
        mapTiles.add(GS);
        MapTile Gdansk = new MapTile("mapTiles/gdansk.jpg", 0, 0);
        mapTiles.add(Gdansk);
        MapTile LS = new MapTile("mapTiles/LS.jpg", -1398, 0);
        mapTiles.add(LS);
        MapTile PS = new MapTile("mapTiles/PS.jpg", 1396, 0);
        mapTiles.add(PS);
        MapTile DS = new MapTile("mapTiles/DS.jpg", 0, 960);
        mapTiles.add(DS);
        MapTile LD = new MapTile("mapTiles/LD.jpg", -1398, 958);
        mapTiles.add(LD);
        MapTile PD = new MapTile("mapTiles/PD.jpg", 1398, 959);
        mapTiles.add(PD);
    }

    public void paint(Graphics g2D){
        for(int i = 0;i < 9;i++)
            g2D.drawImage(mapTiles.get(i).tile, x + mapTiles.get(i).x, y + mapTiles.get(i).y, (int)(mapTiles.get(i).tile.getWidth(null) * scale), (int)(mapTiles.get(i).tile.getHeight(null) * scale), null);
    }
}
