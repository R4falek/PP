package com.company;

public class Bus {
    String line;
    int vehicleCode;
    int id;
    String route;
    int delay;
    double longitude;
    double latitude;
    int x;
    int y;

    public String toString(){
        System.out.println("Line: "+line+" VehicleCode: "+vehicleCode+" id: "+id+" tripId "+route+" Delay: "+delay+" lon: "+longitude+" lat: "+latitude+" x: "+x+" y: "+y);
        return "Line: "+line+" VehicleCode: "+vehicleCode+" id: "+id+" tripId "+route+" Delay: "+delay+" lon: "+longitude+" lat: "+latitude+" x: "+x+" y: "+y;
    }

    public Bus(String _line, int _vehicleCode, int _id, String _route, int _delay, double _longitude, double _latitude){
        line = _line;
        vehicleCode = _vehicleCode;
        id = _id;
        route = _route;
        delay = _delay;
        longitude = _longitude;
        latitude = _latitude;

        setXY(longitude,latitude);
    }

    public void setXY(double longitude, double latitude){
        y = (int)((54.3697 - latitude) / 0.00004151) - 7;
        x = (int)((longitude - 18.590237) / 0.00007164) - 15;
    }

    public boolean isMouseOnIt(int _x, int _y){ return (_x > x && _x < x + 30 && _y > y && _y < y + 15); }
}
