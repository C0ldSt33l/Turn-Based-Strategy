#include <algorithm>

#include "Manager.h"
#include "Map.h"


Manager::Manager() {
    for (int i = 0; i < 4; i++) {
        Message* msg = new Message;
        msg->sender = nullptr;
        msg->set_create(new Unit("texture.png", &map::Map::get_instance()[i * map::MAP_SIZE.x]));
        this->send_messange(msg);
    }

    /*Message* msg = new Message;
    msg->sender = nullptr;
    msg->set_create(new Unit("texture.png", &map::Map::get_instance()[0]));
    this->send_messange(msg);*/
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

        case Message::Type::UNSELECT:
        case Message::Type::MOVE_UNIT:
        case Message::Type::ATTACK:
        case Message::Type::SELECT: {
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

void Manager::draw_units(sf::RenderTarget& target) const {
    for (auto unit : this->units) {
        target.draw(*unit);
    }
}

Manager& Manager::get_instance() {
    static Manager instance;
    return instance;
}
