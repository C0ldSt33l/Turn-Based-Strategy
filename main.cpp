#include<iostream>
#include <SFML/Graphics.hpp>

#include"Map.h"
#include"Cell.h"
#include"Unit.h"


int main(int argc, char* argv[]) {
    sf::RenderWindow window(sf::VideoMode(800, 600), "TBS");
    window.setFramerateLimit(60);

    Map::Map map;

    sf::Texture texture;
    texture.loadFromFile("texture.png");
    
    int i = 0;
    Unit unit(texture);
    unit.setPosition(map.cells[i].getPosition());
    Unit unit2 = unit;
    unit2.setPosition(map.cells[50].getPosition());
    
    sf::Clock clock;
    clock.restart();

    sf::IntRect rect;
    rect.

    while (window.isOpen()) {

    #pragma region Handle Events
        static sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) 
                window.close();
        }
    #pragma endregion

    #pragma region Update
        if (clock.getElapsedTime() >= sf::seconds(1)) {
            clock.restart();
            i = (i + 1) % map.cells.size();
            unit.setPosition(map.cells[i].getPosition());
        }
    #pragma endregion

    #pragma region Draw
        window.clear(sf::Color::White);

        map.draw(window);
        //window.draw(unit);
        unit.draw(window);

        window.draw(unit2);
        window.display();
    #pragma endregion
    }

    return 0;
}