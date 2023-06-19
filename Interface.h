#pragma once

#include "SFML/Graphics.hpp"
#include "Unit.h"


#define UNIT_STRING "HP: {}/{}\nAction: {}\nMove: {}"

class Interface : public sf::Drawable {
    static const std::vector<std::string> TURN_STRINGS;
    static const std::vector<sf::Color> TURN_STRING_COLORS;

    struct Unit_Interface : public sf::Drawable {
        sf::RectangleShape rect;
        sf::Text text;

        Unit_Interface(sf::Font const& font);

        void update();

    private:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    };

    sf::Font font;
    sf::Text turn;

    Unit::Team cur_team;
    Unit_Interface unit_ui;

public:
    Interface(std::string const& file);
    ~Interface();

    void update();

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    static void set_text(sf::Text& text, std::string const& string, sf::Color const& color);
};
