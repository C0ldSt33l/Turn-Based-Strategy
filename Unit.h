#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

#include "Unit.h"
#include "TargetSelect.h"
#include "Message.h"
#include "Map.h"

// TODO:
// implement find futute unit positioin
// 
// change generateId();
// implement targetSelect

class targetSelect;

#define SEMI_TRANSPARENT_COLOR sf::Color{255, 255, 255, 128}

class Unit : public sf::Drawable {
protected:
    const int id;
    int maxHP,
        HP;
    int cellNumber;
    bool has_attacked,
         has_moved;

    std::vector<int> available_zone;

    sf::Texture texture;
    sf::Sprite sprite;

    sf::Sprite future_sprite;

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

public:
    Unit(sf::Texture& const texture, Cell& cell, int health = 100);
    Unit(std::string& const file, Cell& cell, int health = 100);
    Unit(Unit& const unit);
    ~Unit();

    void set_position(sf::Vector2f const& position);
    void set_position(int x, int y);
    void set_position(Cell& cell);
    void set_cellNumber(int number);
    void set_status(Status status);

    int get_id() const;
    sf::Vector2f get_position() const;
    int get_cellNumber() const;
    Status get_status() const;

    //void update() = 0;
    //void sendMessage(Message& const messege) = 0;

    void move_by_mouse(Map::Map& map, sf::Mouse::Button& button, sf::Vector2i const& point);
    void move_by_keyboard(Map::Map& map, sf::Keyboard::Key key);

    void take_damage(int damage);
    void take_heal(int heal);

private:
    static sf::Uint32 generate_id();
    static int move();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};