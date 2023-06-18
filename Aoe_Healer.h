#pragma once

#include "Healer.h"


class Aoe_Healer final : public Healer {
public:
    Aoe_Healer(const Unit::Team team, Cell* cell, std::list<Unit*>* targets);
    ~Aoe_Healer();

    void action(sf::Vector2i const& point);
};

