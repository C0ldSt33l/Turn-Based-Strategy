#include "DMG_Dealer.h"
#include "Manager.h"


DMG_Dealer::DMG_Dealer() : Unit("naoto.png"), damage(50), attack_zone(this->cell, Available_Zone::Type::LINE) {}
DMG_Dealer::~DMG_Dealer() {}

sf::Uint16 DMG_Dealer::get_damage() const {
    return this->damage;
}

void DMG_Dealer::switch_mode() {
    if (this->action_mode == Unit::Mode::MOVING) {
        this->action_mode = Unit::Mode::TAKING_ACTION;
        for (auto cell : this->move_zone.get_zone()) {
            if (!cell) continue;
            cell->set_color(CELL_FILL_COLOR);
        }
        for (auto cell : this->attack_zone.get_zone()) {
            if (!cell) continue;
            cell->set_color(SELECT_COLOR);
        }
    }
    else {
        this->action_mode = Unit::Mode::MOVING;
        for (auto cell : this->attack_zone.get_zone()) {
            if (!cell) continue;
            cell->set_color(CELL_FILL_COLOR);
        }
        for (auto cell : this->move_zone.get_zone()) {
            if (!cell) continue;
            cell->set_color(SEMI_TRANSPARENT_COLOR);
        }
    }
}

void DMG_Dealer::update(sf::RenderWindow const& window, sf::Event const& event) {
    if (!Unit::celected_unit && DMG_Dealer::input_colddown.getElapsedTime().asMilliseconds() >= 250) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->cell->contains(sf::Mouse::getPosition(window))) {
            Message* msg = new Message;
            msg->sender = this;
            msg->set_select(this);
            Manager::get_instance().send_messange(msg);
        }

        return;
    }

    if (this == Unit::celected_unit && DMG_Dealer::input_colddown.getElapsedTime().asSeconds() > 0.3) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
            Message* msg = new Message;
            msg->sender = this;
            msg->set_select(this);
            msg->type = Message::Type::SWITCH_MODE;
            Manager::get_instance().send_messange(msg);
        }

        if (this->action_mode == Unit::Mode::MOVING) {
            this->move_by_mouse(event.mouseButton.button, sf::Mouse::getPosition(window));
        }
        else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            this->attack(sf::Mouse::getPosition(window));
        }
    }
}
void DMG_Dealer::send_message(Message* message) {
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

void DMG_Dealer::attack(sf::Vector2i const& point) {
    Message* msg = new Message;
    msg->sender = this;
    msg->set_select(this);
    msg->type = Message::Type::UNSELECT;
    Manager::get_instance().send_messange(msg);

    for (auto cell : this->attack_zone.get_zone()) {
        if (cell && cell->unit && cell->contains(point)) {
            msg = new Message;
            msg->sender = this;
            msg->set_deal_dmg(this, cell->unit, this->damage);
            Manager::get_instance().send_messange(msg);
        }
    }

    for (auto cell : this->attack_zone.get_zone()) {
        if (!cell) continue;
        cell->set_color(CELL_FILL_COLOR);
    }
}

void DMG_Dealer::move_to(Cell* cell) {
    for (auto cell : this->move_zone.get_zone()) {
        if (!cell || cell == this->cell) continue;
        cell->set_color(CELL_FILL_COLOR);
    }

    if (this->cell) this->cell->make_empty();
    this->cell = cell;
    this->cell->unit = this;

    this->sprite.setPosition(cell->get_position());
    this->projection.setPosition(cell->get_position());

    this->move_zone.update(cell);
    this->attack_zone.update(cell);
}
