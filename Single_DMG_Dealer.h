#pragma once

#include "DMG_Dealer.h"


class Single_DMG_Dealer final : public DMG_Dealer {
public:
    Single_DMG_Dealer(const std::string file, const Unit::Team team, Cell* cell, std::list<Unit*>* targets, Available_Zone const& attack_zone);
    ~Single_DMG_Dealer();

    void action(sf::Vector2i const& point);
};

