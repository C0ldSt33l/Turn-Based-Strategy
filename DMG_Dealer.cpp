#include "DMG_Dealer.h"
#include "Manager.h"


DMG_Dealer::DMG_Dealer(Cell* cell, std::list<Unit*>* targets) : Unit("textures//naoto.png", cell, 100, targets), damage(50), attack_zone(this->cell, Available_Zone::Type::LINE) {}
DMG_Dealer::~DMG_Dealer() {}

sf::Uint16 DMG_Dealer::get_damage() const {
    return this->damage;
}

Available_Zone DMG_Dealer::get_attack_zone() const {
    return this->attack_zone;
}

void DMG_Dealer::set_attack_zone(std::vector<sf::Int32> const& form) {
}

void DMG_Dealer::switch_mode() {
    if (Unit::Mode::MOVING == this->action_mode) {
        this->action_mode = Unit::Mode::TAKING_ACTION;

        this->projection.setPosition(this->sprite.getPosition());
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
            for (auto cell : this->get_attack_zone().get_zone()) {
                if (!cell) continue;
                cell->set_color(CELL_FILL_COLOR);
            }
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
            this->attack_zone.update(this->cell);
        }
        break;
    case Message::Type::SWITCH_MODE:

        if (this == message->select.who_to_select) {
            this->switch_mode();
        }
        break;

    case Message::Type::BUFF:
        break;

    case Message::Type::DEBUFF:
        break;

    default:
        break;
    }

    this->input_colddown.restart();
}

void DMG_Dealer::action(sf::Vector2i const& point) {
    if (!this->has_action_point) return;

    for (auto cell : this->attack_zone.get_zone()) {
        if (cell && cell->unit && cell->contains(point) && this->is_target(cell->unit)) {
            Message* msg = new Message;
            msg->sender = this;
            msg->set_deal_dmg(this, cell->unit, this->damage);
            Manager::get_instance().send_messange(msg);

            break;
        }
    }

    this->has_action_point = false;
    for (auto cell : this->attack_zone.get_zone()) {
        if (!cell) continue;
        cell->set_color(CELL_FILL_COLOR);
    }
}
