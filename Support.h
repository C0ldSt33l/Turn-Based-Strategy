#pragma once

#include"Unit.h"


class Support : public Unit {
public:
    Support(std::string const file, Cell* cell, std::list<Unit*>* targets);
    virtual ~Support();

    void send_message(Message* message);

    void switch_mode();
    void update_zones(Cell* cell);
    virtual void action(sf::Vector2i const& point) = 0;
};