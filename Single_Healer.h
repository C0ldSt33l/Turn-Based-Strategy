#pragma once

#include "Healer.h"


class Single_Healer final : public Healer {
public:
    Single_Healer(const Unit::Team team, Cell* cell, std::list<Unit*>* targets);
    ~Single_Healer();

    void action(sf::Vector2i const& point);
};
