#pragma once

#include <string>

#include "SFML/Graphics.hpp"
#include "Interface.h"


static const sf::Vector2i WINDOW_SIZE	  { 800, 600 };
static const std::string  WINDOW_NAME	  { "TURN-BASED STRATEGY" };
static const sf::Uint32   WINDOW_FRAMERATE{ 60 };

class Game {
    sf::RenderWindow window;
    sf::Event event;

    Interface interface;

public:
    Game();

    void process();
    void update();
    void draw();
};
