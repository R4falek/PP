package com.company;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.awt.*;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.text.SimpleDateFormat;
import java.util.Date;

public class BusStops {
    ArrayList<BusStop> busStops;
    int count;
    String dateString;
    int chosenBusStop = -1;

    public BusStops() throws Exception {
        SimpleDateFormat formatter= new SimpleDateFormat("yyyy-MM-dd");
        Date date = new Date();
        dateString = formatter.format(date);

        busStops = new ArrayList<>();
        getDattaToFile();
        parseData();
        //toString();
    }

    public void getDattaToFile() throws Exception {
        String response = Send_HTTP_Request2.call_me("https://ckan.multimediagdansk.pl/dataset/c24aa637-3619-4dc2-a171-a23eec8f2172/resource/4c4025f0-01bf-41f7-a39f-d156d201b82b/download/stops.json");
        FileWriter file = new FileWriter("busStops.txt");
        file.write(response);
        file.close();
    }

    public String toString(){
        for (BusStop stop : busStops)
            System.out.println(stop.toString());
        System.out.println(busStops.size());
        return null;
    }

    public void parseData() throws IOException, JSONException {
        FileReader reader = new FileReader("busStops.txt");
        int data = reader.read();
        StringBuilder string = new StringBuilder();
        while(data != -1){
            string.append((char) data);
            data = reader.read();
        }
        JSONObject parsedData = new JSONObject(string.toString());
        parsedData = parsedData.getJSONObject(dateString);
        JSONArray stops = parsedData.getJSONArray("stops");

        count = stops.length();

        for(int i = 0;i < stops.length();i++) {
            String name;
            if(stops.getJSONObject(i).isNull("stopName")) name = "";
            else name = stops.getJSONObject(i).getString("stopName");
            String desc = stops.getJSONObject(i).getString("stopDesc");
            int id = stops.getJSONObject(i).getInt("stopId");
            double longitude = stops.getJSONObject(i).getDouble("stopLon");
            double latitude = stops.getJSONObject(i).getDouble("stopLat");

            BusStop busStop = new BusStop(id, name, desc, longitude, latitude);
            busStops.add(busStop);
        }
    }

    public void paint(Graphics g2D, int x, int y, boolean onOff){
        if(!onOff) return;
        for(int i = 0;i < count;i++){
            if(chosenBusStop == busStops.get(i).id) g2D.setColor(Color.green);
            else g2D.setColor(Color.gray);
            g2D.fillOval(busStops.get(i).x + x, busStops.get(i).y + y, 10, 10);
        }
    }

    public void paintChosenBusStop(Graphics g2D, int x, int y){
        if(chosenBusStop == -1) return;
        g2D.setFont(new Font("Arial", Font.PLAIN, 20));
        g2D.setColor(Color.black);
        g2D.drawString(busStops.get(findIndexById(chosenBusStop)).name, busStops.get(findIndexById(chosenBusStop)).x + x - 30, busStops.get(findIndexById(chosenBusStop)).y + y - 10);
    }

    public int stopIdWhichMouseIsOn(int x, int y){
        int returnId = -1;
        for(int i = count - 1;i >= 0;i--) {
            if (busStops.get(i).isMouseOnIt(x, y)) {
                returnId = busStops.get(i).id;
                break;
            }
            returnId = -1;
        }
        return returnId;
    }

    public int findIndexById(int id){
        for(int i = 0;i < count;i++)
            if(id == busStops.get(i).id)
                return i;
        return -1;
    }

    public void setOnTop(int id, boolean onOff){
        if (!onOff) return;
        int index = findIndexById(id);
        if(index >= 0 && index < count){
            busStops.add(busStops.get(index));
            busStops.remove(index);
        }
    }
}
