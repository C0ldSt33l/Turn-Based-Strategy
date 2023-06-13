#pragma once

#include "Unit.h"


class Healer : public Unit{
protected:
    sf::Uint16 heal;

public:
    Healer(std::list<Unit*>* targets = nullptr);
    ~Healer();

    sf::Uint16 get_heal() const;

    virtual void update(sf::RenderWindow const& window, sf::Event const& event);
    virtual void send_message(Message* message);

    virtual void switch_mode();
    void healing(sf::Vector2i point);
};

