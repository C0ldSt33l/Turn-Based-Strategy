#include <iostream>
#include <SFML/Graphics.hpp>
#include <queue>
#include <chrono>

#include "Map.h"
#include "Cell.h"
#include "Unit.h"


void draw_map_cell(Map::Map& map) {
    for (sf::Uint16 i = 0; i < Map::CELL_COUNT; i++) {
        if (!(i % Map::MAP_SIZE.x)) {
            std::cout << '\n';
        }
        std::cout << (map[i].isEmpty() ? "E" : "H");
    }
    
    system("cls");
}

int main(int argc, char* argv[]) {
    sf::RenderWindow window(sf::VideoMode(800, 600), "TBS");
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);

    Map::Map map;

    sf::Texture texture;
    texture.loadFromFile("texture.png");

    Unit unit(texture), unit2(texture);
    unit.setPosition(map[3]);
    unit2.setPosition(map[25]);


    #pragma region Handle Events
    while (window.isOpen()) {
        static sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::KeyPressed:
                unit.moveByKeyboard(map, event.key.code);  
                break;

            case sf::Event::MouseButtonPressed:
                unit.moveByMouse(map, event.mouseButton.button, sf::Mouse::getPosition(window));
                break;

            default:
                break;
            }
        }
    #pragma endregion

    #pragma region Update
        
    #pragma endregion

    #pragma region Draw
        draw_map_cell(map);

        window.clear(sf::Color::White);

        window.draw(map);
        window.draw(unit);
        window.draw(unit2);
        
        window.display();
    #pragma endregion
    }

    return 0;
}