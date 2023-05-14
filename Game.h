#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include "ResourceManager.h"


class Game {
private:
    sf::RenderWindow window;
    //ResourceManager* res_manager;
    enum class Status {
        MAIN_MENU,
        SQUAD_MENU,
        BATTLE,
    };

public:
    Game();
    ~Game();

    void process();

private:
    void menu();

    void draw();
};

