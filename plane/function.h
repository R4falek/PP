//
// Created by student on 15.05.2021.
//

#ifndef PLANE_FUNCTIONS_H
#define PLANE_FUNCTIONS_H

#endif //PLANE_FUNCTIONS_H

#define window_x 1500.0
#define window_y 750.0

float toPixelsX(double value){
    return (float)window_x/2+(window_x*value)/360;
}

float toPixelsY(double value){
    return (float)window_y/2-(window_y*value)/180;
}

void textInstruction(){
    system("clear");
    cout<<"# # # # SKY SCANNER # # # #"<<endl<<endl;
    cout<<"FIND YOUR FLIGHT"<<endl<<endl;
    cout<<"Press I to get instructions"<<endl;
    cout<<"Press E to add a new plane"<<endl;
    cout<<"Press D to delete a plane"<<endl;
    cout<<"LM on the plane to show its details"<<endl;
    cout<<"RM on the plane to open its details"<<endl;
    cout<<"Mouse over the plane to show its details"<<endl;
}

void startInstruction(){
    textInstruction();
    cout<<endl<<endl<<"PRESS SPACE TO START"<<endl;
    while(true){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            break;
    }
}

void instruction(){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::I))
        textInstruction();
}

void planeDataHandler(Plane *p){
    /*int x=0;
    cout<<"Czy pobieramy? x-1-tak";
    cin>>x;
    if(x==1)
        p->getDattaToFile();*/
    p->getDattaFromFile();
}

void planeDeleter(vector<Plane> &planes){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        string nameToDel;
        bool deleted=false;
        system("clear");
        cout<<"Enter the flight code to be delete: ";
        cin >> nameToDel;
        for(int i=0;i<planes.size();i++)
            if(nameToDel==planes[i].getFlight_name()){
                planes.erase(planes.begin()+i);
                cout<<"Deleted"<<endl;
                deleted= true;
            }
        if(!deleted)
            cout<<"Not found"<<endl;
    }
}

void planeDataUpdate(vector<Plane> &planes){
    for(int i=0;i<planes.size();i++){
        //planes[i].getDattaToFile();
        planes[i].getDattaFromFile();
    }
}

static Plane addPlane(){
    system("clear");
    string name;
    cout<<"Enter the flight code: ";
    cin>>name;
    Plane p(name);
    planeDataHandler(&p);
    while(!p.getIsGood()) {
        cout<<"Try again: ";
        cin>>name;
        p.setFlight_name(name);
        planeDataHandler(&p);
    }
    return p;
}

void openDetails(vector<Plane> planes, sf::RenderWindow& window){
        if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
            for(int i=0;i<planes.size();i++)
                if(!planes.empty() and sf::Mouse::getPosition(window).x>toPixelsX(planes[i].getLongitude())-20 and sf::Mouse::getPosition(window).x<toPixelsX(planes[i].getLongitude())+20 and sf::Mouse::getPosition(window).y>toPixelsY(planes[i].getLatitude())-20 and sf::Mouse::getPosition(window).y<toPixelsY(planes[i].getLatitude())+30){
                        string command="gio open "+planes[i].getFlight_name()+".json";
                        system(command.c_str());
                    }
                }
        }


int modeToDisplayDetails(vector<Plane> planes, sf::RenderWindow& window){
    static int t;
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        t=-1;
        for(int i=0;i<planes.size();i++)
            if(!planes.empty() and sf::Mouse::getPosition(window).x>toPixelsX(planes[i].getLongitude())-20 and sf::Mouse::getPosition(window).x<toPixelsX(planes[i].getLongitude())+20 and sf::Mouse::getPosition(window).y>toPixelsY(planes[i].getLatitude())-20 and sf::Mouse::getPosition(window).y<toPixelsY(planes[i].getLatitude())+30){
                t=i;
            }
    }
    return t;
}

void displayDetails(vector<Plane> planes, sf::RenderWindow& window, int mode){
    if(mode!=-1 and !planes.empty()){
        window.draw(Plane::createPoint(planes[mode].getDepLongitude(),planes[mode].getDepLatitude(),"dep"));
        window.draw(Plane::createPoint(planes[mode].getArrLongitude(),planes[mode].getArrLatitude(),"arr"));
        window.draw(Plane::createText(planes[mode].getFlight_name(), toPixelsX(planes[mode].getLongitude())-20, toPixelsY(planes[mode].getLatitude())-30));
        window.draw(Plane::createText(planes[mode].getDepCity(),toPixelsX(planes[mode].getDepLongitude())-20,toPixelsY(planes[mode].getDepLatitude())-30));
        window.draw(Plane::createText(planes[mode].getArrCity(),toPixelsX(planes[mode].getArrLongitude())-20,toPixelsY(planes[mode].getArrLatitude())-30));
        window.draw(Plane::createText(planes[mode].getFlight_name()+"   Latitude: "+ to_string(planes[mode].getLatitude())+"   Longitude: "+to_string(planes[mode].getLongitude())+"   From: "+planes[mode].getDepCity()+"   To: "+planes[mode].getArrCity(),20,window_y+10));
    }
}

void drawOnWindow(vector<Plane> planes, sf::RenderWindow& window){
    for(int i=0;i<planes.size();i++){
        if(sf::Mouse::getPosition(window).x>toPixelsX(planes[i].getLongitude())-20 and sf::Mouse::getPosition(window).x<toPixelsX(planes[i].getLongitude())+20 and sf::Mouse::getPosition(window).y>toPixelsY(planes[i].getLatitude())-20 and sf::Mouse::getPosition(window).y<toPixelsY(planes[i].getLatitude())+30){
            window.draw(Plane::createPoint(planes[i].getDepLongitude(),planes[i].getDepLatitude(),"dep"));
            window.draw(Plane::createPoint(planes[i].getArrLongitude(),planes[i].getArrLatitude(),"arr"));
            window.draw(Plane::createText(planes[i].getFlight_name(), toPixelsX(planes[i].getLongitude())-20, toPixelsY(planes[i].getLatitude())-30));
            window.draw(Plane::createText(planes[i].getDepCity(),toPixelsX(planes[i].getDepLongitude())-20,toPixelsY(planes[i].getDepLatitude())-30));
            window.draw(Plane::createText(planes[i].getArrCity(),toPixelsX(planes[i].getArrLongitude())-20,toPixelsY(planes[i].getArrLatitude())-30));
        }
        window.draw(planes[i].setPlane(0));
    }
}