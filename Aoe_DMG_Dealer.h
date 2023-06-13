#pragma once

#include "DMG_Dealer.h"


class Aoe_DMG_Dealer : public DMG_Dealer {
public:
    Aoe_DMG_Dealer(Cell* cell, std::list<Unit*>* targets);
    ~Aoe_DMG_Dealer();

    void action(sf::Vector2i const& point);
};

