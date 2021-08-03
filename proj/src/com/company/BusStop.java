package com.company;

public class BusStop {
    int id;
    String name;
    String desc;
    double longitude;
    double latitude;
    int x;
    int y;

    public BusStop(int _id, String _name, String _desc, double _longitude, double _latitude){
        id = _id;
        name = _name;
        desc = _desc;
        latitude = _latitude;
        longitude = _longitude;

        setXY(longitude, latitude);
    }

    public void setXY(double longitude, double latitude){
        y = (int)((54.3697 - latitude) / 0.00004151) - 5;
        x = (int)((longitude - 18.590237) / 0.00007164) - 5;
    }

    public String toString(){
        System.out.println("id: "+id+" Name: "+name+" lon: "+longitude+" lat: "+latitude+" x: "+x+" y: "+y);
        return "id: "+id+" Name: "+name+" lon: "+longitude+" lat: "+latitude+" x: "+x+" y: "+y;
    }

    public boolean isMouseOnIt(int _x, int _y){
        return _x > x && _x < x + 10 && _y > y && _y < y + 10;
    }
}
