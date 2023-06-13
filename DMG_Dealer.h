#pragma once

#include "Unit.h"


class DMG_Dealer : public Unit {
protected:
    sf::Uint16 damage;
    Available_Zone attack_zone;

public:
    DMG_Dealer(Cell* cell, std::list<Unit*>* targets);
    virtual ~DMG_Dealer();

    sf::Uint16 get_damage() const;
    Available_Zone get_attack_zone() const;

    void set_attack_zone(std::vector<sf::Int32> const& form);

    void send_message(Message* message);

    void switch_mode();
    virtual void action(sf::Vector2i const& point);
};

