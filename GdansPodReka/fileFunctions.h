#include <iostream>
#include<json-c/json.h>
#include <curl/curl.h>
#include <vector>
#include "Vehicle.h"

using namespace std;

void getDataToFile() {
    CURL *curl;
    FILE *fp;

    fp=fopen("buses.json", "wb");

    curl=curl_easy_init();

    curl_easy_setopt(curl, CURLOPT_URL,"https://ckan2.multimediagdansk.pl/gpsPositions");

    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

    CURLcode result = curl_easy_perform(curl);

    if(result==CURLE_OK)
        cout<<"Download successful"<<endl;
    else
        cout<<"ERROR: "<<curl_easy_strerror(result);

    fclose(fp);

    curl_easy_cleanup(curl);
}

void listOfVehicles(const vector<Vehicle>& vehicleType,int line){
    for(auto & vehicle : vehicleType)
        if(vehicle.getLineNumber()==line)
            cout<<vehicle.getLineNumber()<<" "<<vehicle.getDelay()<<" "<<vehicle.getLongitude()<<" "<<vehicle.getLatitude()<<" "<<vehicle.getX()<<" "<<vehicle.getY()<<endl;
}

void listOfVehicles(const vector<Vehicle>& vehicleType){
    for(auto & vehicle : vehicleType)
            cout<<vehicle.getLineNumber()<<" "<<vehicle.getDelay()<<" "<<vehicle.getLongitude()<<" "<<vehicle.getLatitude()<<" "<<vehicle.getX()<<" "<<vehicle.getY()<<endl;
}

void createVehiclesWithData(vector<Vehicle> &vehicleType,int lambdaX, int lambdaY){
    FILE *fp;
    char buff[200000];

    struct json_object *parsed_json;
    struct json_object *vehicles;
    struct json_object *vehicle;
    struct json_object *line;
    struct json_object *delay;
    struct json_object *longitude;
    struct json_object *latitude;

    fp = fopen("buses.json","r");

    if ( fp == nullptr ) {
        cout<<"FILE ERROR: "<<endl;
        return;
    }
    fread(buff, sizeof(buff), 1, fp);
    fclose(fp);

    parsed_json = json_tokener_parse(buff);

    json_object_object_get_ex(parsed_json, "Vehicles", &vehicles);

    size_t n_vehicles =json_object_array_length(vehicles);
    int n_existingVehicles=0;

    for(int i=0;i<n_vehicles;i++){
        vehicle=json_object_array_get_idx(vehicles,i);

        json_object_object_get_ex(vehicle, "Line", &line);
        json_object_object_get_ex(vehicle, "Lon", &longitude);
        json_object_object_get_ex(vehicle, "Lat", &latitude);
        json_object_object_get_ex(vehicle, "Delay", &delay);
        n_existingVehicles++;

        Vehicle v(json_object_get_int(line), json_object_get_double(longitude), json_object_get_double(latitude),
                  json_object_get_int(delay),lambdaX,lambdaY);
        vehicleType.push_back(v);

    }
}