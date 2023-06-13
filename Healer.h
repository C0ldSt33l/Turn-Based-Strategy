#pragma once

#include "Support.h"


class Healer : public Support {
protected:
    sf::Uint16 heal;

public:
    Healer(Cell* cell, std::list<Unit*>* targets);
    ~Healer();

    sf::Uint16 get_heal() const;

    void action(sf::Vector2i const& point);
};

