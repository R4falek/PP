//
// Created by student on 17.05.2021.
//

#ifndef KRAKOWPODREKA_VEHICLE_H
#define KRAKOWPODREKA_VEHICLE_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;

double XX=18.645690;
double YY=54.347747;

class Vehicle {
    int lineNumber;
    double longitude;
    double latitude;
    double x;
    double y;
    int tripID;
public:
    Vehicle(int lineNumber, double longitude, double latitude, int id, int lambdaX, int lambdaY){
        this->lineNumber=lineNumber;
        this->longitude=longitude;
        this->latitude=latitude;
        this->tripID=id;
        this->x=824.69-(XX-longitude)*18503.2533-3+lambdaX;
        this->y=145.551-(YY-latitude)*-31607.1661-3+lambdaY;
    }
    int getLineNumber() const {return lineNumber;}
    double getLongitude() const {return longitude;}
    double getLatitude() const {return latitude;}
    int getID() const {return tripID;}
    double getX()const{return x;}
    double getY()const{return y;}
    void setX(double _x){this->x=_x;}
    void setY(double _y){this->y=_y;}
};


#endif //KRAKOWPODREKA_VEHICLE_H
