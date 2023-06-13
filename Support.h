#pragma once

#include"Unit.h"


class Support : public Unit {
protected:
    

public:
    Support(std::string const file, Cell* cell, std::list<Unit*>* targets);
    virtual ~Support();

    void send_message(Message* message);

    void switch_mode();
    virtual void action(sf::Vector2i const& point) = 0;
};