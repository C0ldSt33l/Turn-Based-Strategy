#pragma once

#include "SFML/Graphics.hpp"


#define UNIT_STRING "HP: {}/{}\nAction: {}\nMove: {}"

class Unit;
class Interface : public sf::Drawable {
    struct Unit_Interface : public sf::Drawable {
        Unit* selected_unit;

        sf::RectangleShape rect;
        sf::Text text;

        Unit_Interface(sf::Font const& font);

        void update();

    private:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    };

    sf::Font font;
    sf::Text turn;

    Unit_Interface unit_ui;

    const std::string PLAYER_TURN = "Player turn";
    const std::string ENEMY_TURN = "Enemy turn";

public:
    Interface(std::string const& file);
    ~Interface();

    void update();

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    static void set_text(sf::Text& text, std::string const& string, sf::Color const& color);
};
