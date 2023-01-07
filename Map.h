#pragma once
#include<vector>
#include<SFML/Graphics.hpp>

#include"Cell.h"


namespace Map{
    const float        CELL_SIZE{ 75 };
    const sf::Vector2f START_POS{ 80, 60 };

    class Map {
        sf::Vector2i size;
        sf::Sprite background;

    public:
        std::vector<sf::RectangleShape> cells;

        Map(sf::Vector2i size = { 9, 7 });
        ~Map();

        void draw(sf::RenderWindow& window);
    };
}
