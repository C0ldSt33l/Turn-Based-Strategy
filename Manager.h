#pragma once

#include <list>

#include "Unit.h"
#include "Message.h"


class Manager {
    std::list<Unit*> units;
    std::list<Message*> messages;

    Manager();
    ~Manager();

public:
    Manager(Manager const&) = delete;
    Manager& operator=(Manager const&) = delete;

    void update(sf::RenderWindow const& window, sf::Event const& event);
    void send_messange(Message* message);

    void draw_units(sf::RenderTarget& target) const;


    static Manager& get_instance();
};
