#pragma once

#include "Support.h"


class Healer : public Support {
protected:
    sf::Uint16 heal;

public:
    using Support::Support;
    ~Healer();

    sf::Uint16 get_heal() const;

    virtual void action(sf::Vector2i const& point) = 0;
};

