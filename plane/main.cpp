#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Plane.h"
#include "function.h"

using namespace std;

int main() {
    vector<Plane> planes;

    sf::Event event;

    startInstruction();

    sf::RenderWindow window(sf::VideoMode(window_x,window_y+40), "SKY SCANNER");
    window.setFramerateLimit(20);

    sf::Texture texture;
    texture.loadFromFile("mapa2.png");
    sf::Sprite sprite(texture);
    system("clear");

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            switch (event.type) {
                case (sf::Event::EventType::Closed):
                    window.close();
                    break;
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
                planes.push_back(addPlane());

        window.clear();
        window.draw(sprite);

        window.draw(Plane::createText("Press I to get instructions",window_x-200,window_y+10));
        instruction();

        if(!planes.empty()){
           /* for(int i=0;i<planes.size();i++)
                cout<<planes[i].getFlight_name()<<" ";
            cout<<endl;*/
            planeDataUpdate(planes);
            planeDeleter(planes);
            openDetails(planes,window);
            displayDetails(planes,window, modeToDisplayDetails(planes,window));
            drawOnWindow(planes, window);
        }

        window.display();
    }

    return 0;
}