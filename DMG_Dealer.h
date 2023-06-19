#pragma once

#include "Unit.h"
#include "Available_Zone.h"


class DMG_Dealer : public Unit {
protected:
    sf::Uint16 damage;
    Available_Zone attack_zone;

public:
    DMG_Dealer(std::string const file, sf::Uint16 damage, Cell* cell, std::list<Unit*>* targets, Available_Zone attack_zone);
    virtual ~DMG_Dealer();

    sf::Uint16 get_damage() const;
    Available_Zone get_attack_zone() const;

    void set_attack_zone(std::vector<sf::Int32> const& form);

    void send_message(Message* message);

    void switch_mode();
    void update_zones(Cell* cell);
    virtual void action(sf::Vector2i const& point) = 0;
};

