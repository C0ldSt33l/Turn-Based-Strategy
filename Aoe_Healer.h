#pragma once

#include "Healer.h"


class Aoe_Healer : public Healer {
public:
    Aoe_Healer(Cell* cell, std::list<Unit*>* targets);
    ~Aoe_Healer();

    void action(sf::Vector2i const& point);
};

