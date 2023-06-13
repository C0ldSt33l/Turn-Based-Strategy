#include <algorithm>

#include "Manager.h"
#include "Map.h"
#include "DMG_Dealer.h"
#include "Aoe_Healer.h"
#include "Single_Healer.h"


Manager::Manager() {
    Message* msg;
        
   /* msg = new Message;
    msg->sender = nullptr;
    msg->set_create(new DMG_Dealer(&map::Map::get_instance()[0], &this->units));
    this->send_messange(msg);

    msg = new Message;
    msg->sender = nullptr;
    DMG_Dealer* unit = new DMG_Dealer(&map::Map::get_instance()[8], &this->units);
    unit->set_attack_zone(Available_Zone::invert_form(Available_Zone::Type::LINE));
    msg->set_create(unit);
    this->send_messange(msg);

    msg = new Message;
    msg->sender = nullptr;
    msg->set_create(new DMG_Dealer(&map::Map::get_instance()[7], &this->units));
    this->send_messange(msg);*/

    msg = new Message;
    msg->sender = nullptr;
    msg->set_create(new Aoe_Healer(&map::Map::get_instance()[22], &this->units));
    this->send_messange(msg);

    msg = new Message;
    msg->sender = nullptr;
    msg->set_create(new Single_Healer(&map::Map::get_instance()[21], &this->units));
    this->send_messange(msg);
}
Manager::~Manager() {
    for (auto unit : this->units) {
        delete unit;
    }
    this->units.clear();

    for (auto msg : this->messages) {
        delete msg;
    }
    this->messages.clear();
}

void Manager::update(sf::RenderWindow const& window, sf::Event const& event) {
    for (auto unit : this->units) {
        unit->update(window, event);
    }

    Message* cur_msg;
    while (!this->messages.empty()) {
        cur_msg = this->messages.back();
        this->messages.pop_back();

        switch (cur_msg->type) {
        case Message::Type::KILL: {
            auto dead_body = std::find(this->units.cbegin(), this->units.cend(), cur_msg->kill.who_to_kill);
            delete *dead_body;
            this->units.erase(dead_body);
        } break;

        case Message::Type::CREATE: {
            this->units.push_back(cur_msg->create.new_unit);
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
}
void Manager::send_messange(Message* message) {
    this->messages.push_back(message);
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
