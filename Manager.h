#pragma once

#include <list>

#include "Message.h"


class Unit;
class Manager {
    Unit::Team cur_team;
    std::list<Unit*> units;
    std::list<Message*> messages;
    std::vector<std::list<Unit*>> teams;

    Manager();
    ~Manager();

public:
    Manager(Manager const&) = delete;
    Manager& operator=(Manager const&) = delete;

    void update(sf::RenderWindow const& window, sf::Event const& event);
    void send_messange(Message* message);
    void add_unit(const Unit::Team team, const Unit::Type type, const sf::Uint16 cell_number);
    void next_turn();

    Unit::Team get_cur_team() const;
    std::list<Unit*> const& get_units() const;

    void draw_units(sf::RenderTarget& target) const;

    static Manager& get_instance();

private:
    void del_unit(Unit* unit);
    Unit* create_unit(const Unit::Team team, const Unit::Type type, const sf::Uint16 cell_number);
};
