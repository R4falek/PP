//
// Created by student on 18.05.2021.
//

#ifndef KRAKOWPODREKA_WINDOWFUNCTIONS_H
#define KRAKOWPODREKA_WINDOWFUNCTIONS_H

#endif //KRAKOWPODREKA_WINDOWFUNCTIONS_H

int lambdaX=0;
int lambdaY=0;

void textInstruction(){
    //system("clear");
    cout<<"# # # # Gdansk pod reka # # # #"<<endl<<endl;
    cout<<"Mapa pokazuje aktualna lokalizacje autobusow i tramwajow w Gdansku"<<endl<<endl;
    cout<<"Aby wyswietlic dana linie kliknij spacje i wpisz do konsoli"<<endl;
    cout<<"Aby wyswietlic z powrotem wszystkie pojazdy kliknij spacje"<<endl;
    cout<<"Poruszaj sie za pomoca 'w''s''a''d'"<<endl;
}

void instruction(sf::Font &font,sf::RenderWindow &window,sf::Event &event){
    sf::Text text;
    text.setFont(font);
    text.setOutlineColor(sf::Color::Blue);
    text.setOutlineThickness(1);
    text.setFillColor(sf::Color::White);
    text.setScale(1.f,1.f);
    text.setPosition(500,300);
    text.setString("\t\t\t\t\t\t\t# # # # Gdansk pod reka # # # #\n\nMapa pokazuje aktualna lokalizacje autobusow i tramwajow w Gdansku\n\t\t\tAby wyswietlic dana linie kliknij spacje i wpisz do konsoli\n"
                   "\t\t  Aby wyswietlic z powrotem wszystkie pojazdy kliknij spacje\n\t\t\t\t\t\t\t Poruszaj sie za pomoca 'w''s''a''d'\n\n\t\t\t\t\t\t\t\t  PRESS SPACE TO START");
    window.clear(sf::Color(72 ,61 ,139));
    window.draw(text);
    window.display();
    textInstruction();
    cout<<endl<<endl<<"PRESS SPACE TO START"<<endl;
    while(true){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            break;
    }
}

void mapMoving(vector<sf::Sprite>&sprites, sf::Event &event,vector<Vehicle>&buses,vector<double>&coordsX,vector<double>&coordsY){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) and lambdaX<2060) {
        lambdaX+=20;
        for(auto &X:coordsX)
            X+=20;
        for (auto &vehicle : buses)
            vehicle.setX(vehicle.getX() + 20);
        for(auto &sprite : sprites)
            sprite.setPosition(sprite.getPosition().x + 20, sprite.getPosition().y);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) and lambdaX>-1800) {
        lambdaX-=20;
        for(auto &X:coordsX)
            X-=20;
        for (auto &vehicle : buses)
            vehicle.setX(vehicle.getX() - 20);
        for(auto &sprite : sprites)
            sprite.setPosition(sprite.getPosition().x - 20, sprite.getPosition().y);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) and lambdaY<1820) {
        lambdaY+=20;
        for(auto &Y:coordsY)
            Y+=20;
        for (auto &vehicle : buses)
            vehicle.setY(vehicle.getY() + 20);
        for(auto &sprite : sprites)
            sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y + 20);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) and lambdaY>-1200) {
        lambdaY-=20;
        for(auto &Y:coordsY)
            Y-=20;
        for (auto &vehicle : buses)
            vehicle.setY(vehicle.getY() - 20);
        for(auto &sprite : sprites)
            sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y - 20);
    }

    /*sf::Event::MouseWheelMoved;
    if(event.mouseWheelScroll.delta==1 and sprite.getScale().x<1){
        //sprite.setOrigin(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y);
        scale+=0.05;
        sprite.setScale(sprite.getScale().x+0.05,sprite.getScale().y+0.05);
    }
    if(event.mouseWheelScroll.delta==-1 and sprite.getScale().x>0.2){
        //sprite.setOrigin(sf::Mouse::getPosition(window).x-sprite.getPosition().x,sf::Mouse::getPosition(window).y-sprite.getPosition().y);
        scale-=0.05;
        sprite.setScale(sprite.getScale().x-0.05,sprite.getScale().y-0.05);
    }
    event.mouseWheelScroll.delta=0;*/
}

void drawBuses(vector<Vehicle>&buses,vector<sf::CircleShape>&busPoints,vector<sf::Text>&lineNumbers,sf::RenderWindow &window,int lookFor){
    if(lookFor==-1){
        for(int i=0;i<busPoints.size();i++){
                busPoints[i].setPosition(buses[i].getX(),buses[i].getY());
                window.draw(busPoints[i]);
        }
        for(int i=0;i<lineNumbers.size();i++){
                lineNumbers[i].setPosition(buses[i].getX(),buses[i].getY());
                window.draw(lineNumbers[i]);
        }
    }
    for(int i=0;i<busPoints.size();i++){
        if(buses[i].getLineNumber()==lookFor){
            busPoints[i].setPosition(buses[i].getX(),buses[i].getY());
            window.draw(busPoints[i]);
        }
    }
    for(int i=0;i<lineNumbers.size();i++){
        if(buses[i].getLineNumber()==lookFor){
            lineNumbers[i].setPosition(buses[i].getX(),buses[i].getY());
            window.draw(lineNumbers[i]);
        }
    }
}

void setUpMap(vector<sf::Sprite>&mapTiles){
    static sf::Texture textureLG;
    textureLG.loadFromFile("LG.jpg");
    sf::Sprite spriteLG(textureLG);
    spriteLG.setOrigin(2576,1764);
    spriteLG.setScale(0.4,0.4);
    spriteLG.setPosition(-1035,-1127);
    mapTiles.push_back(spriteLG);

    static sf::Texture texturePG;
    texturePG.loadFromFile("PG.jpg");
    sf::Sprite spritePG(texturePG);
    spritePG.setOrigin(2576,1764);
    spritePG.setScale(0.4,0.4);
    spritePG.setPosition(2693,-1127);
    mapTiles.push_back(spritePG);

    static sf::Texture textureGS;
    textureGS.loadFromFile("GS.jpg");
    sf::Sprite spriteGS(textureGS);
    spriteGS.setOrigin(2576,1764);
    spriteGS.setScale(0.4,0.4);
    spriteGS.setPosition(830,-1127);
    mapTiles.push_back(spriteGS);

    static sf::Texture texture;
    texture.loadFromFile("gdansk.jpg");
    sf::Sprite sprite(texture);
    sprite.setOrigin(2576,1764);
    sprite.setScale(0.4,0.4);
    sprite.setPosition(830,150);
    mapTiles.push_back(sprite);

    static sf::Texture textureLS;
    textureLS.loadFromFile("LS.jpg");
    sf::Sprite spriteLS(textureLS);
    spriteLS.setOrigin(2576,1764);
    spriteLS.setScale(0.4,0.4);
    spriteLS.setPosition(-1035,150);
    mapTiles.push_back(spriteLS);

    static sf::Texture texturePS;
    texturePS.loadFromFile("PS.jpg");
    sf::Sprite spritePS(texturePS);
    spritePS.setOrigin(2576,1764);
    spritePS.setScale(0.4,0.4);
    spritePS.setPosition(2693,150);
    mapTiles.push_back(spritePS);

    static sf::Texture textureDS;
    textureDS.loadFromFile("DS.jpg");
    sf::Sprite spriteDS(textureDS);
    spriteDS.setOrigin(2576,1764);
    spriteDS.setScale(0.4,0.4);
    spriteDS.setPosition(830,1427);
    mapTiles.push_back(spriteDS);


    static sf::Texture textureLD;
    textureLD.loadFromFile("LD.jpg");
    sf::Sprite spriteLD(textureLD);
    spriteLD.setOrigin(2576,1764);
    spriteLD.setScale(0.4,0.4);
    spriteLD.setPosition(-1035,1427);
    mapTiles.push_back(spriteLD);

    static sf::Texture texturePD;
    texturePD.loadFromFile("PD.jpg");
    sf::Sprite spritePD(texturePD);
    spritePD.setOrigin(2576,1764);
    spritePD.setScale(0.4,0.4);
    spritePD.setPosition(2693,1427);
    mapTiles.push_back(spritePD);
}