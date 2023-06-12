#pragma once

#include "Unit.h"


class DMG_Dealer : public Unit {
protected:
    sf::Uint16 damage;
    Available_Zone attack_zone;

public:
    DMG_Dealer();
    virtual ~DMG_Dealer();

    sf::Uint16 get_damage() const;
    void switch_mode();

    virtual void update(sf::RenderWindow const& window, sf::Event const& event);
    virtual void send_message(Message* message);

    void attack(sf::Vector2i const& point);
    void move_to(Cell* cell);

    friend class Unit;
};

