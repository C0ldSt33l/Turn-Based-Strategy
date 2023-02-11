#pragma once
#include<vector>
#include<SFML/Graphics.hpp>

#include"Cell.h"


namespace Map{
    static const sf::Vector2i MAP_SIZE{ 9, 7 };

    static const sf::Vector2f CELL_SIZE{ 75, 75 };
    static const sf::Vector2f START_POS{ 80, 60 };
    static const int          CELL_COUNT{ MAP_SIZE.x * MAP_SIZE.y - 1 };

    #define CELL_THICKNESS 5
    
    class Map : public sf::Drawable {
        sf::Vector2i size;
        std::vector<Cell> cells;
        //sf::Sprite background;

    public:
        Map(sf::Vector2i size = MAP_SIZE);
        ~Map();

        Cell operator[](int i) const;

    private:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    };
}
