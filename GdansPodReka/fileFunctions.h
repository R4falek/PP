#include <iostream>
#include<json-c/json.h>
#include <curl/curl.h>
#include <vector>
#include <ctime>
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
            cout<<vehicle.getLineNumber()<<" "<<vehicle.getID()<<" "<<vehicle.getLongitude()<<" "<<vehicle.getLatitude()<<" "<<vehicle.getX()<<" "<<vehicle.getY()<<endl;
}

void listOfVehicles(const vector<Vehicle>& vehicleType){
    for(auto & vehicle : vehicleType)
            cout<<vehicle.getLineNumber()<<" "<<vehicle.getID()<<" "<<vehicle.getLongitude()<<" "<<vehicle.getLatitude()<<" "<<vehicle.getX()<<" "<<vehicle.getY()<<endl;
}

void createVehiclesWithData(vector<Vehicle> &vehicleType,int lambdaX, int lambdaY){
    FILE *fp;
    char buff[200000];

    struct json_object *parsed_json;
    struct json_object *vehicles;
    struct json_object *vehicle;
    struct json_object *line;
    struct json_object *tripID;
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
        json_object_object_get_ex(vehicle, "Route", &tripID);
        n_existingVehicles++;

        Vehicle v(json_object_get_int(line), json_object_get_double(longitude), json_object_get_double(latitude),
                  json_object_get_int(tripID),lambdaX,lambdaY);
        vehicleType.push_back(v);

    }
}
bool getPathToFile(int route, int trip) {
    CURL *curl;
    FILE *fp;
    bool isgood=true;

    fp=fopen("path.json", "wb");

    curl=curl_easy_init();

    time_t now = time(0);
    tm *ltm = localtime(&now);

    string month=to_string(1+ltm->tm_mon);
    if(1+ltm->tm_mon<10){
        month="0"+to_string(1+ltm->tm_mon);
    }

    string day=to_string(ltm->tm_mday);
    if(ltm->tm_mday<10){
        day="0"+to_string(ltm->tm_mday);
    }

    string url="https://ckan2.multimediagdansk.pl/shapes?date="+ to_string(1900+ltm->tm_year)+"-"+month+"-"+
                                                                                          day+"&routeId="+ to_string(route)+"&tripId="+
                                                                                                     to_string(trip);
    cout<<url<<endl;
    curl_easy_setopt(curl, CURLOPT_URL,url.c_str());

    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

    CURLcode result = curl_easy_perform(curl);

    if(result==CURLE_OK)
        cout<<"Download successful"<<endl;
    else{
        cout<<"ERROR: "<<curl_easy_strerror(result);
        isgood=false;
    }

    fclose(fp);

    curl_easy_cleanup(curl);

    return isgood;
}
void createPath(vector<double> &pathX,vector<double> &pathY,int lambdaX, int lambdaY){
    FILE *fp;
    char buff[200000];

    struct json_object *parsed_json;
    struct json_object *coordinates;
    struct json_object *point;
    struct json_object *point_cords;


    fp = fopen("path.json","r");

    if ( fp == nullptr ) {
        cout<<"FILE ERROR: "<<endl;
        return;
    }
    fread(buff, sizeof(buff), 1, fp);
    fclose(fp);

    parsed_json = json_tokener_parse(buff);

    json_object_object_get_ex(parsed_json, "coordinates", &coordinates);

    if(!coordinates)
        return;

    size_t n_vehicles =json_object_array_length(coordinates);
    int n_existingVehicles=0;

    double XX=18.645690;
    double YY=54.347747;

    for(int i=0;i<n_vehicles;i++){
        point=json_object_array_get_idx(coordinates,i);
        for(int j=0;j<2;j++) {
            point_cords = json_object_array_get_idx(point, j);
            if(j==0)
                pathX.push_back(824.69-(XX-json_object_get_double(point_cords))*18503.2533-3+lambdaX);
            else
                pathY.push_back(145.551-(YY-json_object_get_double(point_cords))*-31607.1661-3+lambdaY);
        }
        n_existingVehicles++;
    }
}