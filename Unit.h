#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

#include "Map.h"


#define SEMI_TRANSPARENT_COLOR sf::Color{ 255, 255, 255, 128 }
#define SELECT_COLOR           sf::Color::Red

struct Message;
class Unit : public sf::Drawable {
    const sf::Uint16 id;

protected:
    static Unit* celected_unit;

    int maxHP,
        HP;
    bool has_attacked,
         has_moved;

    sf::Uint16 cell_number;
    Cell* cell;

    sf::Texture texture;
    sf::Sprite sprite;

    sf::Sprite future_sprite;

    bool is_selected;

public:
    enum class Status {
        NONE = 2,
        UNDEFEADABLE,
        ATK_BUFF,
        DEF_BUFF,
        HP_BUFF,
        STUN,
        POISON,
        HIDDEN,
    };
    Status status;

    Unit();
    Unit(sf::Texture const& texture, Cell* cell, int health = 100);
    Unit(std::string const file, Cell* cell, int health = 100);
    Unit(Unit const& unit);
    virtual ~Unit();
    Unit& operator=(Unit const& unit);

    void set_position(sf::Vector2f const& position);
    void set_position(int x, int y);
    void set_position(Cell& cell);
    void set_cellNumber(sf::Uint16 number);
    void set_status(Status status);
    void set_texture(sf::Texture const& texture);
    void set_sprite_color(sf::Color const& color);
    void set_selected_unit(sf::Vector2i const& point);

    sf::Uint16 get_id() const;
    sf::Vector2f get_position() const;
    int get_cellNumber() const;
    Status get_status() const;
    sf::Texture get_texture() const;

    void update(sf::RenderWindow const& window, sf::Event const& event);

    void move_by_mouse(sf::Mouse::Button const& button, sf::Vector2i const& point);
    void move_by_keyboard(sf::Keyboard::Key const& key);

    void take_damage(Unit* attacker, sf::Uint16 damage);
    void take_heal(Unit* healer, sf::Uint16 heal);

private:
    static sf::Uint16 generate_id();
    static sf::Sprite set_sprite(sf::Texture const& texture, sf::Vector2f const& pos);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};