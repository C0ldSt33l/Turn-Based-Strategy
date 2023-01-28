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

    std::string file = "texture.png";
    Unit unit(file);
    unit.setPosition(map.getCellPosition(5));
    std::cout << unit.getId() << "\n";

    Unit unit2(file);
    unit2.setPosition(map.getCellPosition(5));
    std::cout << unit2.getId() << "\n";

    while (window.isOpen()) {

    #pragma region Handle Events
        static sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) 
                window.close();
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