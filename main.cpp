#include <iostream>
#include <SFML/Graphics.hpp>
#include <queue>
#include <chrono>

#include "Map.h"
#include "Cell.h"
#include "Unit.h"


int main(int argc, char* argv[]) {
    sf::RenderWindow window(sf::VideoMode(800, 600), "TBS");
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);

    Map::Map map;

    sf::Texture texture;
    texture.loadFromFile("texture.png");
    
    sf::Sprite sprite(texture);
    sf::Color color;

    Unit unit(texture, map[3]), unit2(texture, map[25]);

    #pragma region Handle Events
    sf::Event event;
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::KeyPressed:
                //unit.move_by_keyboard(map, event.key.code);
                break;

            case sf::Event::MouseButtonPressed:
                //unit.move_by_mouse(map, event.mouseButton.button, sf::Mouse::getPosition(window));
                break;

            default:
                break;
            }
        }
    #pragma endregion

    #pragma region Update
        unit.move_by_mouse(map, event.mouseButton.button, sf::Mouse::getPosition(window));
        //unit.move_by_keyboard(map, event.key.code);
    #pragma endregion

    #pragma region Draw
        map.draw_unit_position();

        window.clear(sf::Color::White);

        window.draw(map);
        window.draw(unit);
        window.draw(unit2);
        
        window.display();
    #pragma endregion
    }

    return 0;
}