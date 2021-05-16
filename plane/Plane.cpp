//
// Created by student on 15.05.2021.
//

#include <iostream>
#include<json-c/json.h>
#include<curl/curl.h>
#include <string>
#include <cmath>
#include "Plane.h"

#define window_x 1500.0
#define window_y 750.0

void Plane::getDattaToFile() const {
    FILE *fp;
    string url="https://flight-data4.p.rapidapi.com/get_flight_info?flight="+flight_name;
    string filename=flight_name+".json";
    fp=fopen(filename.c_str(), "wb");

    CURL *hnd = curl_easy_init();

    curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "GET");
    curl_easy_setopt(hnd, CURLOPT_URL, url.c_str());

    struct curl_slist *headers = nullptr;
    headers = curl_slist_append(headers, "x-rapidapi-key: 19d92447damsh97b8b45025423e1p156a72jsnbb00b7a5fd94");
    headers = curl_slist_append(headers, "x-rapidapi-host: flight-data4.p.rapidapi.com");
    curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, headers);

    curl_easy_setopt(hnd, CURLOPT_WRITEDATA, fp);
    curl_easy_setopt(hnd, CURLOPT_FAILONERROR, 1L);

    CURLcode ret = curl_easy_perform(hnd);

    if(ret==CURLE_OK)
        cout<<"Downloas succesful!"<<endl;
    else
        cout<<"ERROR: "<<curl_easy_strerror(ret)<<endl;
    fclose(fp);

    curl_easy_cleanup(hnd);
}

void Plane::getDattaFromFile(){
    this->isGood=true;
    FILE *fp;
    string filename=flight_name+".json";
    char buff[2000];
    string name=this->flight_name;
    struct json_object *parsed_json;
    struct json_object *flight_name;
    struct json_object *flight;
    struct json_object *latitude;
    struct json_object *longitude;
    struct json_object *airport;
    struct json_object *city;

    fp = fopen(filename.c_str(),"r");
    if ( fp == nullptr ) {
        cout<<"FILE ERROR: "<<this->flight_name<<".json"<<endl;
        this->isGood=false;
        return;
    }
    fread(buff, sizeof(buff), 1, fp);
    fclose(fp);

    parsed_json = json_tokener_parse(buff);

    json_object_object_get_ex(parsed_json, name.c_str(), &flight_name);

    if(flight_name== nullptr){
        this->latitude=0;
        this->longitude=0;
        this->dep_city="";
        this->dep_latitude=0;
        this->dep_longitude=0;
        this->arr_city="";
        this->arr_latitude=0;
        this->arr_longitude=0;
        this->rotation=0;
        return;
    }

    json_object_object_get_ex(flight_name, "flight", &flight);

    json_object_object_get_ex(flight, "latitude", &latitude);
    this->latitude= json_object_get_double(latitude);
    json_object_object_get_ex(flight, "longitude", &longitude);
    this->longitude= json_object_get_double(longitude);

    json_object_object_get_ex(flight_name, "dep_airport", &airport);
    json_object_object_get_ex(airport, "city", &city);
    this->dep_city= json_object_get_string(city);
    json_object_object_get_ex(airport, "latitude", &latitude);
    this->dep_latitude= json_object_get_double(latitude);
    json_object_object_get_ex(airport, "longitude", &longitude);
    this->dep_longitude= json_object_get_double(longitude);

    json_object_object_get_ex(flight_name, "arr_airport", &airport);
    json_object_object_get_ex(airport, "city", &city);
    this->arr_city= json_object_get_string(city);
    json_object_object_get_ex(airport, "latitude", &latitude);
    this->arr_latitude= json_object_get_double(latitude);
    json_object_object_get_ex(airport, "longitude", &longitude);
    this->arr_longitude= json_object_get_double(longitude);

    double h=abs(this->latitude-this->arr_latitude+3);
    double w=abs(this->longitude-this->arr_longitude+3);
    rotation=atan(h/w)* 180 / M_PI;

    if(this->arr_longitude>this->longitude and this->arr_latitude<this->latitude)
        rotation-=180;
    if(this->arr_longitude>this->longitude and this->arr_latitude>this->latitude)
        rotation=-rotation-180;
    if(this->arr_longitude<this->longitude and this->arr_latitude>this->latitude)
        rotation=atan(h/w)* 180 / M_PI;
    if(this->arr_longitude<this->longitude and this->arr_latitude<this->latitude){
        rotation=-rotation;
    }
}

sf::CircleShape Plane::createPoint(double lon, double lat, const string& mode) {
    sf::CircleShape shape(6.f);
    if(mode=="dep")
        shape.setFillColor(sf::Color::Red);
    if(mode=="arr")
        shape.setFillColor(sf::Color::Green);
    shape.setOutlineThickness(1);
    shape.setOutlineColor(sf::Color::Black);
    shape.setPosition(window_x/2+(window_x*lon)/360-3,window_y/2-(window_y*lat)/180-3);
    return shape;
}

sf::Sprite Plane::setPlane(int textureMode) const {
    static sf::Texture texture,textureSelected;
    texture.loadFromFile("plane.png");
    textureSelected.loadFromFile("planeSelected.png");
    sf::Sprite plane;
    if(textureMode==1)
        plane.setTexture(textureSelected);
    else
        plane.setTexture(texture);
    plane.setOrigin(plane.getTexture()->getSize().x*0.5,plane.getTexture()->getSize().y*0.5);
    plane.setScale(0.1,0.1);
    plane.setRotation(rotation-90);
    plane.setPosition(window_x/2+(window_x*longitude)/360,window_y/2-(window_y*latitude)/180);
    plane.move(0,0);
    return plane;
}

sf::Text Plane::createText(const string& str, const double x, const double y) {
    static sf::Font font;
    font.loadFromFile("/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf");
    static sf::Text text;
    text.setFont(font);
    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(2);
    text.setFillColor(sf::Color::Green);
    text.setScale(0.5f,0.5f);
    text.setString(str);
    text.setPosition(x,y);
    return text;
}
