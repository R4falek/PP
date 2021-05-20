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
        textInstruction();
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
                while(isThereANumber== false){
                    cout<<"Podaj numer lini: ";
                    cin>>lookFor;
                    for(auto &bus:buses)
                        if(bus.getLineNumber()==lookFor)
                            isThereANumber=true;
                }
            }
            else
                lookFor=-1;
        }

        mapMoving(mapTiles, event,buses);
        window.clear();
        for(auto &tile:mapTiles)
            window.draw(tile);
        drawBuses(buses,busPoints,lineNumbers,window,lookFor);

        window.display();
    }

    return 0;
}