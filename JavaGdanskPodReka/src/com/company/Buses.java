package com.company;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.awt.*;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;

public class Buses {
    ArrayList<Bus> buses;
    int count;
    int chosenBusId = -1;
    ArrayList<Object> pathPoints;

    public Buses() throws Exception {
        buses = new ArrayList<>();
        pathPoints = new ArrayList<>();
        getDattaToFile("https://ckan2.multimediagdansk.pl/gpsPositions", "buses.txt");
        parseData();
        //buses.toString();
    }
    
    public void getDattaToFile(String url, String filePath) throws Exception {
        String response = Send_HTTP_Request2.call_me(url);
        FileWriter file = new FileWriter(filePath);
        file.write(response);
        file.close();
    }

    public void parseData() throws IOException, JSONException {
        FileReader reader = new FileReader("buses.txt");
        int data = reader.read();
        StringBuilder string = new StringBuilder();
        while(data != -1){
            string.append((char) data);
            data = reader.read();
        }
        JSONObject parsedData = new JSONObject(string.toString());
        JSONArray vehicles = parsedData.getJSONArray("Vehicles");

        count = vehicles.length();

        for(int i = 0;i < vehicles.length();i++) {
            String line = vehicles.getJSONObject(i).getString("Line");
            int vehicleCode = vehicles.getJSONObject(i).getInt("VehicleCode");
            int id = vehicles.getJSONObject(i).getInt("VehicleId");
            String route = vehicles.getJSONObject(i).getString("Route");
            int delay = vehicles.getJSONObject(i).getInt("Delay");
            double longitude = vehicles.getJSONObject(i).getDouble("Lon");
            double latitude = vehicles.getJSONObject(i).getDouble("Lat");

            Bus bus = new Bus(line, vehicleCode, id, route, delay, longitude, latitude);
            buses.add(bus);
        }
    }

    public String toString(){
        for (Bus bus : buses)
            System.out.println(bus.toString());
        System.out.println(buses.size());
        return null;
    }

    public void reset(){
        buses.clear();
        count=0;
    }

    public void refresh() throws Exception {
        reset();
        getDattaToFile("https://ckan2.multimediagdansk.pl/gpsPositions", "buses.txt");
        parseData();
    }

    public int busIdWhichMouseIsOn(int x, int y, String onOff){
        if(onOff != null) return chosenBusId;
        int returnId = -1;
        for(int i = count - 1;i >= 0;i--) {
            if (buses.get(i).isMouseOnIt(x, y)) {
                returnId = buses.get(i).id;
                break;
            }
            returnId = -1;
        }
        return returnId;
    }

    public void paint(Graphics g2D, int x, int y, boolean onOff){
        if(!onOff) return;
        for(int i = 0;i < count;i++){
            g2D.setColor(new Color(190, 130, 230));
            if(chosenBusId == buses.get(i).id)
                g2D.setColor(Color.green);
            g2D.fillRect(buses.get(i).x + x, buses.get(i).y + y, 30, 15);
            g2D.setColor(Color.BLACK);
            g2D.drawRect(buses.get(i).x + x, buses.get(i).y + y, 30, 15);
            g2D.drawString(buses.get(i).line, buses.get(i).x + x + 6, buses.get(i).y + y + 12);
        }
    }

    public int findIndexById(int id){
        for(int i = 0;i < count;i++)
            if(id == buses.get(i).id)
                return i;
        return -1;
    }

    public void setOnTop(int id, boolean onOff){
        if(!onOff) return;
        int index = findIndexById(id);
        if(index >= 0 && index < count){
            buses.add(buses.get(index));
            buses.remove(index);
        }
    }

    public String findRouteById(int id){
        if(id != -1) return buses.get(findIndexById(id)).route;
        return null;
    }

    public String findLineById(int id){
        if(id != -1) return buses.get(findIndexById(id)).line;
        return null;
    }

    public int setY(double latitude){ return (int)(((54.3697 - latitude) / 0.00004151)); }

    public int setX(double longitude){ return (int)(((longitude - 18.590237) / 0.00007164)); }

    public void parsePathData() throws IOException, JSONException {
        FileReader reader = new FileReader("busPath.txt");
        int data = reader.read();
        StringBuilder string = new StringBuilder();
        while(data != -1){
            string.append((char) data);
            data = reader.read();
        }
        JSONObject parsedData = new JSONObject(string.toString());
        JSONArray coordinates = parsedData.getJSONArray("coordinates");

        for (int i = 0;i < coordinates.length();i++){
            JSONArray point = coordinates.getJSONArray(i);
            pathPoints.add(setX((Double) point.get(0)));
            pathPoints.add(setY((Double) point.get(1)));
        }
    }

    public void getBusPath() throws Exception {
        if(chosenBusId == -1) return;
        SimpleDateFormat formatter= new SimpleDateFormat("yyyy-MM-dd");
        Date date = new Date();
        getDattaToFile("https://ckan2.multimediagdansk.pl/shapes?date="+formatter.format(date)+"&routeId="+findLineById(chosenBusId)+"&tripId="+findRouteById(chosenBusId), "busPath.txt");
        pathPoints.clear();
        parsePathData();
    }

    public void paintPath(Graphics g2D, int x, int y, int onOff){
        if(onOff == -1) return;
        g2D.setColor(Color.green);
        for(int i = 0;i < pathPoints.size() - 3;i--)
            g2D.drawLine((int)pathPoints.get(i++) + x, (int)pathPoints.get(i++) + y,(int)pathPoints.get(i++) + x, (int)pathPoints.get(i) + y);
    }
}
