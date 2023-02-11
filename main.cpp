#include<iostream>
#include <SFML/Graphics.hpp>
#include<queue>

#include"Map.h"
#include"Cell.h"
#include"Unit.h"


int main(int argc, char* argv[]) {
    sf::RenderWindow window(sf::VideoMode(800, 600), "TBS");
    window.setFramerateLimit(60);

    Map::Map map;

    sf::Texture texture;
    texture.loadFromFile("texture.png");

    Unit unit(texture);
    unit.setPosition(map[50].getPosition());
    unit.setCellNumber(50);

    while (window.isOpen()) {
    #pragma region Handle Events
        static sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:     window.close();
                                        break;
            case sf::Event::KeyPressed: unit.moveByKeyboard(map, event.key.code);  
                                        break;
            default: break;
            }
        }
    #pragma endregion

    #pragma region Update
        
    #pragma endregion

    #pragma region Draw
        window.clear(sf::Color::White);

        window.draw(map);
        window.draw(unit);

        window.display();
    #pragma endregion
    }

    return 0;
}