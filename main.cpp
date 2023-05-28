#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>

#include "Manager.h"


int main(int argc, char* argv[]) {
    sf::RenderWindow window(sf::VideoMode(800, 600), "TBS");
    window.setFramerateLimit(60);
    //window.setKeyRepeatEnabled(false);

    #pragma region Handle Events
    sf::Event event;
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::KeyPressed:
                break;

            case sf::Event::MouseButtonPressed:
                break;

            default:
                break;
            }
        }
    #pragma endregion

    #pragma region Update

    #pragma endregion
        
    #pragma region Draw
        window.clear(sf::Color::White);

        //Manager::get_instance().draw_map(window);
        window.draw(map::Map::get_instance());
        Manager::get_instance().draw_units(window);

        window.display();
    #pragma endregion
    }

    return 0;
}