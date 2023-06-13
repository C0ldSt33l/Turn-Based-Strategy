#include "Healer.h"
#include "Manager.h"


Healer::Healer(std::list<Unit*>* targets) : Unit("textures//hakumen.png", 100, targets), heal(50) {}
Healer::~Healer() {}

sf::Uint16 Healer::get_heal() const {
    return this->heal;
}

void Healer::update(sf::RenderWindow const& window, sf::Event const& event) {
    if (!Unit::celected_unit && Unit::input_colddown.getElapsedTime().asMilliseconds() >= 250) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->cell->contains(sf::Mouse::getPosition(window))) {
            Message* msg = new Message;
            msg->sender = this;
            msg->set_select(this);
            Manager::get_instance().send_messange(msg);
        }

        return;
    }

    if (this != Unit::celected_unit || Unit::input_colddown.getElapsedTime().asSeconds() <= 0.3)
        return;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || !this->has_action_point || !this->has_move_point && !this->has_action_point) {
        Message* msg = new Message;
        msg->type = Message::Type::UNSELECT;
        msg->sender = msg->select.who_to_select = this;
        Manager::get_instance().send_messange(msg);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
        Message* msg = new Message;
        msg->sender = this;
        msg->set_select(this);
        msg->type = Message::Type::SWITCH_MODE;
        Manager::get_instance().send_messange(msg);
    }

    if (Unit::Mode::MOVING == this->action_mode) {
        this->move_by_mouse(event.mouseButton.button, sf::Mouse::getPosition(window));
    }
    else if (Unit::Mode::TAKING_ACTION == this->action_mode && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        this->healing(sf::Mouse::getPosition(window));
    }
}
void Healer::send_message(Message* message) {
    switch (message->type) {
    case Message::Type::SELECT:
        if (this == message->select.who_to_select) {
            this->make_selected();
        }
        break;

    case Message::Type::UNSELECT:
        if (this == message->select.who_to_select) {
            this->make_unselected();
        }
        break;

    case Message::Type::DEAL_DMG:
        if (this == message->take_dmg.who_to_attack) {
            this->take_damage(message->take_dmg.attacker, message->take_dmg.damage);
        }
        break;

    case Message::Type::HEAL:
        if (this == message->heal.who_to_heal) {
            this->take_heal(message->heal.healer, message->heal.heal);
        }
        break;

    case Message::Type::MOVE:
        if (this == message->move.who_to_move) {
            this->move_to(message->move.destination);
        }
        break;

    case Message::Type::SWITCH_MODE:
        if (this == message->select.who_to_select) {
            this->switch_mode();
        }
        break;

    default:
        break;
    }

    this->input_colddown.restart();
}

void Healer::switch_mode() {
    if (Unit::Mode::MOVING == this->action_mode) {
        this->action_mode = Unit::Mode::TAKING_ACTION;

        this->projection.setPosition(this->sprite.getPosition());
        for (auto cell : this->move_zone.get_zone()) {
            if (!cell) continue;
            cell->set_color(CELL_FILL_COLOR);
        }
        for (auto unit : *this->targets) {
            if (this == unit) continue;
            unit->cell->set_color(SELECT_COLOR);
        }
    }
    else {
        this->action_mode = Unit::Mode::MOVING;

        for (auto unit : *this->targets) {
            if (this == unit) continue;
            unit->cell->set_color(CELL_FILL_COLOR);
        }
        for (auto cell : this->move_zone.get_zone()) {
            if (!cell) continue;
            cell->set_color(SEMI_TRANSPARENT_COLOR);
        }
    }
}
void Healer::healing(sf::Vector2i point) {
    if (!this->has_action_point) return;

    for (auto unit : *this->targets) {
        if (this == unit) continue;

        if (unit->cell->contains(point)) {
            this->has_action_point = false;

            Message* msg = new Message;
            msg->sender = this;
            msg->set_heal(this->heal, this, unit);
            Manager::get_instance().send_messange(msg);

            break;
        }
    }

    for (auto unit : *this->targets) {
        if (this == unit) continue;
        unit->cell->set_color(CELL_FILL_COLOR);
    }
}
