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
    static enum class Type {
        AOE_DMG_DEALER,
        SINGLE_DMG_DEALER,
        AOE_HEALER,
        SINGLE_HEALER,
        BUFFER,
        DEBUFFER,
    };
    static enum class Mode {
        MOVING,
        TAKING_ACTION
    };
    enum class Team {
        PLAYER,
        ENEMY,
    };

    static Unit* celected_unit;

private:
    const sf::Uint16 id;

protected:
    static sf::Clock input_colddown;

    sf::Int32 max_hp,
              cur_hp;
    bool has_action_point,
         has_move_point;

    Cell* cell;

    sf::Texture texture;
    sf::Sprite sprite;
    sf::Sprite projection;

    Unit::Team team;
    Unit::Mode action_mode;

    std::list<Unit*>* targets;

public:
    Available_Zone move_zone;

    Unit(std::string const file, Cell* cell, sf::Int32 health, std::list<Unit*>* targets);
    Unit(Unit const& unit);
    virtual ~Unit();
    Unit& operator=(Unit const& unit);

    void set_position(sf::Vector2f const& position);
    void set_position(int x, int y);
    void set_texture(sf::Texture const& texture);
    void set_sprite_color(sf::Color const& color);

    void make_selected();
    void make_unselected();
    void reset_points();

    sf::Uint16 get_id() const;
    sf::Int32 get_hp() const;
    sf::Int32 get_max_hp() const;
    Unit::Team get_team() const;
    Cell* get_cell() const;
    bool get_action_point() const;
    bool get_move_point() const;
    sf::Vector2f get_position() const;
    sf::Texture get_texture() const;

    bool has_any_points() const;
    bool is_target(Unit const* unit) const;

    void update(sf::RenderWindow const& window, sf::Event const& event);
    virtual void send_message(Message* message) = 0;
    virtual void action(sf::Vector2i const& point) = 0;
    virtual void update_zones(Cell* cell) = 0;
    virtual void switch_mode() = 0;

    void move_to(Cell* cell);
    void move_by_mouse(sf::Mouse::Button const& button, sf::Vector2i const& point);
    void move_by_keyboard(sf::Keyboard::Key const& key);
    void move_projection(Cell const* cell);

    void take_damage(Unit* attacker, sf::Uint16 damage);
    void take_heal(Unit* healer, sf::Uint16 heal);

    friend std::ostream& operator<<(std::ostream& out, Unit const& unit);

    friend class Support;
    friend class Aoe_Healer;
    friend class Single_Healer;

private:
    static sf::Uint16 generate_id();
    static sf::Sprite set_sprite(sf::Texture const& texture, sf::Vector2f const& pos);
    static Unit* get_selected_unit();

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};