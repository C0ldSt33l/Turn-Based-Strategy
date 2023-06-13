#pragma once

#include "Healer.h"


class Single_Healer : public Healer {
public:
    Single_Healer(Cell* cell, std::list<Unit*>* targets);
    ~Single_Healer();

    void action(sf::Vector2i const& point);
};
