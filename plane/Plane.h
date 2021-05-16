//
// Created by student on 15.05.2021.
//

#ifndef PLANE_PLANE_H
#define PLANE_PLANE_H

#include <iostream>
#include<json-c/json.h>
#include <SFML/Graphics.hpp>
#include<curl/curl.h>
#include <string>

using namespace std;

class Plane {
    string flight_name;
    double latitude;
    double longitude;
    string dep_city;
    double dep_latitude;
    double dep_longitude;
    string arr_city;
    double arr_latitude;
    double arr_longitude;
    double rotation;
    bool isGood;
public:
    explicit Plane(const string &name){this->flight_name=name;}
    ~Plane(){
        string name=flight_name+".json";
        //remove(name.c_str());
    };
    void getDattaToFile()const;
    void getDattaFromFile();
    string getFlight_name()const{return flight_name;}
    void setFlight_name(const string& name){this->flight_name=name;}
    string getDepCity()const{return dep_city;}
    string getArrCity()const{return arr_city;}
    static sf::CircleShape createPoint(double lon, double lat, const string& mode);
    sf::Sprite setPlane(int textureMode) const;
    static sf::Text createText(const string& str, double x, double y);
    double getLatitude() const {return latitude;}
    double getLongitude() const {return longitude;}
    double getDepLatitude() const {return dep_latitude;}
    double getDepLongitude() const {return dep_longitude;}
    double getArrLatitude() const {return arr_latitude;}
    double getArrLongitude() const {return arr_longitude;}
    bool getIsGood() const{return isGood;}
};

#endif //PLANE_PLANE_H
