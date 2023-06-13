#pragma once

#include"Unit.h"


class Support : public Unit {
protected:
    

public:
    Support();
    virtual ~Support();

    virtual void update(sf::RenderWindow const& window, sf::Event const& event);
    virtual void send_message(Message* message);

    virtual void switch_mode();
    void buff();
};