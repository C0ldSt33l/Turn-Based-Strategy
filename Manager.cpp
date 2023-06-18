#include <algorithm>

#include "Manager.h"
#include "Map.h"
#include "Single_DMG_Dealer.h"
#include "Aoe_DMG_Dealer.h"
#include "Aoe_Healer.h"
#include "Single_Healer.h"


Manager::Manager() : cur_team(Unit::Team::ENEMY){
    this->teams.resize(2);

    this->add_unit(Unit::Team::PLAYER, Unit::Type::SINGLE_DMG_DEALER, 0);
    this->add_unit(Unit::Team::PLAYER, Unit::Type::SINGLE_DMG_DEALER, 1);
    this->add_unit(Unit::Team::PLAYER, Unit::Type::SINGLE_DMG_DEALER, 3);
    this->add_unit(Unit::Team::PLAYER, Unit::Type::AOE_HEALER, 22);
    this->add_unit(Unit::Team::ENEMY, Unit::Type::SINGLE_DMG_DEALER, 7);
    this->add_unit(Unit::Team::ENEMY, Unit::Type::SINGLE_DMG_DEALER, 8);
}
Manager::~Manager() {
    for (auto unit : this->units) {
        delete unit;
    }
    this->units.clear();
    for (auto team : this->teams) {
        team.clear();
    }

    for (auto msg : this->messages) {
        delete msg;
    }
    this->messages.clear();
}

void Manager::update(sf::RenderWindow const& window, sf::Event const& event) {
    if (!Unit::celected_unit) {
        for (auto unit : this->teams[int(this->cur_team)]) {
            unit->update(window, event);
        }
    }
    else {
        for (auto unit : this->units) {
            unit->update(window, event);
        }
    }
    

    Message* cur_msg;
    while (!this->messages.empty()) {
        cur_msg = this->messages.back();
        this->messages.pop_back();

        switch (cur_msg->type) {
        case Message::Type::KILL: {
            this->del_unit(cur_msg->kill.who_to_kill);
        } break;

        case Message::Type::CREATE: {
            Unit* new_unit = cur_msg->create.new_unit;
            this->teams[static_cast<int>(new_unit->get_team())].push_back(new_unit);
            this->units.push_back(new_unit);
        } break;

        case Message::Type::NEXT_TURN: {
            this->next_turn();
        } break;

        case Message::Type::SELECT:
        case Message::Type::UNSELECT:
        case Message::Type::SWITCH_MODE:
        case Message::Type::MOVE:
        case Message::Type::DEAL_DMG:
        case Message::Type::HEAL: {
            for (auto unit : this->units) {
                unit->send_message(cur_msg);
            }
        } break;

        default:
            break;
        }
    }

    cur_msg = new Message;
    cur_msg->sender = nullptr;
    cur_msg->type = Message::Type::NEXT_TURN;
    this->send_messange(cur_msg);
}
void Manager::send_messange(Message* message) {
    this->messages.push_back(message);
}

void Manager::add_unit(const Unit::Team team, const Unit::Type type, const sf::Uint16 cell_number) {
    Message* msg = new Message;
    msg->sender = nullptr;
    msg->set_create(Manager::create_unit(team, type, cell_number));
    Manager::send_messange(msg);
}
void Manager::next_turn() {
    for (auto unit : this->teams[int(this->cur_team)]) {
        if (unit->has_any_points()) return;
    }

    int team = !int(this->cur_team);
    for (auto unit : this->teams[team]) {
        unit->reset_points();
    }
    this->cur_team = static_cast<Unit::Team>(team);
}

std::list<Unit*> const& Manager::get_units() const {
    return this->units;
}

void Manager::draw_units(sf::RenderTarget& target) const {
    for (auto unit : this->units) {
        target.draw(*unit);
    }
}

Manager& Manager::get_instance() {
    static Manager instance;
    return instance;
}

Unit* Manager::create_unit(const Unit::Team team, const Unit::Type type, const sf::Uint16 cell_number) {
    Unit* unit = nullptr;
    int index = static_cast<int>(team);

    switch (type) {
    case Unit::Type::AOE_HEALER:
        unit = new Aoe_Healer(team, &map::Map::get_instance()[cell_number], &this->teams[index]);
        break;

    case Unit::Type::SINGLE_HEALER:
        unit = new Single_Healer(team, &map::Map::get_instance()[cell_number], &this->teams[index]);
        break;

    case Unit::Type::AOE_DMG_DEALER:
        unit = new Aoe_DMG_Dealer(team, &map::Map::get_instance()[cell_number], &this->teams[!index]);
        break;

    case Unit::Type::SINGLE_DMG_DEALER:
        unit = new Single_DMG_Dealer(team, &map::Map::get_instance()[cell_number], &this->teams[!index]);
        break;

    case Unit::Type::BUFFER:
        break;

    case Unit::Type::DEBUFFER:
        break;
    }

    return unit;
}

void Manager::del_unit(Unit* unit) {
    int team = static_cast<int>(unit->get_team());
    auto it = std::find(this->teams[team].cbegin(), this->teams[team].cend(), unit);
    this->teams[team].erase(it);

    auto dead_body = std::find(this->units.cbegin(), this->units.cend(), unit);
    delete* dead_body;
    this->units.erase(dead_body);
}
