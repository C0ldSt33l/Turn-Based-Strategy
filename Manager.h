#pragma once

#include <list>

#include "Unit.h"
#include "Message.h"


class Manager {
    Unit* selected_unit;
    std::list<Unit*> units;
    std::list<Message*> messages;

    Manager();
    ~Manager();

public:
    Manager(Manager const&) = delete;
    Manager& operator=(Manager const&) = delete;

    void update();
    void send_messange(Message* message);

    void draw_units(sf::RenderTarget& target) const;

    void select_cur_unit();

    static Manager& get_instance();
};

