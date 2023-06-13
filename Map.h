#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

#include "Cell.h"


namespace map {
    const sf::Vector2i        MAP_SIZE              { 9, 7 };

    static const sf::Vector2f CELL_SIZE             { 65, 65 };
    static const float        CELL_OUTLINE_THICKNESS{ 5 };
    static const sf::Vector2f START_POS             { 130, 40 };
    static const int          CELL_COUNT            { MAP_SIZE.x * MAP_SIZE.y };

    #define CELL_FILL_COLOR    sf::Color::Green
    #define SELECTED_CELL_FILL_COLOR sf::Color::Blue
    #define CELL_OUTLINE_COLOR sf::Color(23, 56 ,195)
    
    class Map : public sf::Drawable {
        sf::Vector2i size;
        std::vector<Cell> cells;
        //sf::Sprite background;

        Map(sf::Vector2i size = MAP_SIZE);
        ~Map();

    public:
        Map(Map const&) = delete; 
        Map& operator=(Map const&) = delete;

        static Map& get_instance();

        void draw_unit_position() const;

        Cell& operator[](sf::Uint16 i);
        Cell const& get_cell(sf::Uint16 i) const;

    private:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    };
}
