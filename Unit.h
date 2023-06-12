#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <list>

#include "Map.h"
#include "Message.h"
#include "Available_Zone.h"


#define SEMI_TRANSPARENT_COLOR sf::Color{ 255, 255, 255, 128 }
#define DEFAULT_COLOR          sf::Color{ 255, 255, 255, 255 }
#define SELECT_COLOR           sf::Color::Red

struct Message;
class Unit : public sf::Drawable {
public:
    enum class Status {
        NONE,
        UNDEFEADABLE,
        ATK_BUFF,
        DEF_BUFF,
        HP_BUFF,
        STUN,
        POISON,
        HIDDEN,
    };
    enum class Type {
        DMG_DEALER,
        HEALER,
    };
    enum class Mode {
        MOVING,
        TAKING_ACTION
    };

    static Unit* celected_unit;

private:
    const sf::Uint16 id;

protected:
    static sf::Clock input_colddown;

    int max_hp,
        cur_hp;
    bool has_attacked,
         has_moved;

    Cell* cell;

    sf::Texture texture;
    sf::Sprite sprite;

    sf::Sprite projection;

    Status status;
    Mode action_mode;

    Available_Zone move_zone;

public:
    Unit(std::string const file, int health = 100, Available_Zone::Type move_zone = Available_Zone::Type::RECT);
    Unit(Unit const& unit);
    virtual ~Unit();
    Unit& operator=(Unit const& unit);

    void set_position(sf::Vector2f const& position);
    void set_position(int x, int y);
    void set_status(Status status);
    void set_texture(sf::Texture const& texture);
    void set_sprite_color(sf::Color const& color);
    void make_selected();
    void make_unselected();
    virtual void switch_mode() = 0;

    sf::Uint16 get_id() const;
    sf::Vector2f get_position() const;
    int get_cellNumber() const;
    Status get_status() const;
    sf::Texture get_texture() const;

    virtual void update(sf::RenderWindow const& window, sf::Event const& event) = 0;
    virtual void send_message(Message* message) = 0;    

    virtual void move_to(Cell* cell);
    void move_by_mouse(sf::Mouse::Button const& button, sf::Vector2i const& point);
    void move_by_keyboard(sf::Keyboard::Key const& key);
    void move_projection(Cell const* cell);

    void take_damage(Unit* attacker, sf::Uint16 damage);
    void take_heal(Unit* healer, sf::Uint16 heal);

private:
    static sf::Uint16 generate_id();
    static sf::Sprite set_sprite(sf::Texture const& texture, sf::Vector2f const& pos);
    static Unit* get_selected_unit();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};