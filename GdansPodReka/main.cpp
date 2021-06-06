#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "fileFunctions.h"
#include "windowFunctions.h"
#include "Vehicle.h"

using namespace std;

int main(){
    vector<Vehicle> buses;
    vector<sf::CircleShape> busPoints;
    vector<sf::Text> lineNumbers;
    vector<sf::Sprite> mapTiles;
    vector<double>coordsX;
    vector<double>coordsY;

    cout.precision(17);

    sf::Event event;

    getDataToFile();
    createVehiclesWithData(buses,lambdaX,lambdaY);
    listOfVehicles(buses,999);

    sf::RenderWindow window(sf::VideoMode(1920,1080), "Gdansk pod reka");
    window.setFramerateLimit(80);

    sf::Font font;
    font.loadFromFile("/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf");

    instruction(font,window,event);

    setUpMap(mapTiles);

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            switch (event.type) {
                case (sf::Event::EventType::Closed):
                    window.close();
                    break;
            }
        }
        //textInstruction();
        static int delayDownload=400;
        if(delayDownload==400){
            buses.clear();
            busPoints.clear();
            lineNumbers.clear();
            getDataToFile();
            createVehiclesWithData(buses,lambdaX,lambdaY);
            for(auto & buse : buses){
                sf::CircleShape shap(6.f);
                shap.setFillColor(sf::Color::Green);
                if(buse.getLineNumber()<20)
                    shap.setFillColor(sf::Color::Red);
                shap.setOutlineThickness(1);
                shap.setOutlineColor(sf::Color::Black);
                shap.setPosition(buse.getX(),buse.getY());
                busPoints.push_back(shap);
                sf::Text text;
                text.setFont(font);
                text.setOutlineColor(sf::Color::Black);
                text.setOutlineThickness(3);
                text.setFillColor(sf::Color::White);
                text.setScale(0.6f,0.6f);
                text.setString(to_string(buse.getLineNumber()));
                text.setPosition(buse.getX(),buse.getY());
                lineNumbers.push_back(text);
            }
            delayDownload=0;
        }
        delayDownload++;

        static int lookFor=-1;
        int x=sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
        if(x){
            while(x)
                x=sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
            if(lookFor==-1){
                bool isThereANumber= false;
                while(!isThereANumber){
                    cout<<"Podaj numer lini: ";
                    cin>>lookFor;
                    for(auto &bus:buses)
                        if(bus.getLineNumber()==lookFor){
                            isThereANumber=true;
                            if(getPathToFile(lookFor,bus.getID()))
                                createPath(coordsX,coordsY,lambdaX,lambdaY);
                        }
                }
            }
            else{
                lookFor=-1;
                coordsX.clear();
                coordsY.clear();
            }

        }

        mapMoving(mapTiles, event,buses,coordsX,coordsY);
        window.clear();
        for(auto &tile:mapTiles)
            window.draw(tile);
        for(int i=0;i<coordsX.size();i+=2){
            sf::CircleShape sha(2.f);
            sha.setFillColor(sf::Color::Blue);
            sha.setOutlineThickness(1);
            sha.setOutlineColor(sf::Color::Black);
            sha.setPosition(coordsX[i],coordsY[i+1]);
            window.draw(sha);
        }
        drawBuses(buses,busPoints,lineNumbers,window,lookFor);
        /*if(false){
            sf::RectangleShape sp(sf::Vector2f(400,100));
            sp.setFillColor(sf::Color(72 ,61 ,139));
            sp.setPosition(1650,0);
            window.draw(sp);
            sf::Text t;
            t.setPosition(1680,10);
            t.setString("Podaj numer lini");
            t.setFont(font);
            t.setOutlineColor(sf::Color::Blue);
            t.setOutlineThickness(1);
            t.setFillColor(sf::Color::White);
            t.setScale(1.f,1.f);
            window.draw(t);

            sf::Event::TextEntered;
            int n=event.key.code-48,numer=event.key.code-48;
            cout<<"numer"<<numer<<endl;
            if(numer>=0 and numer<10){
                cout<<"f";
                while(numer==n){
                    n=sf::Event::TextEntered;
                    cout<<"l";
                }

                cout<<to_string(numer)<<endl;
            }
        }*/
        window.display();
    }

    return 0;
}