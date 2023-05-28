#pragma once

#include "Unit.h"


class DMG_Dealer : public Unit {
protected:
    sf::Uint16 damage;

public:
    DMG_Dealer();
    DMG_Dealer(DMG_Dealer const& dmg_dealer);
    virtual ~DMG_Dealer();

    void attack();
};

