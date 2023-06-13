#include "Support.h"


Support::Support(std::string const file, Cell* cell, std::list<Unit*>* targets) : Unit(file, cell, 100, targets) {}
Support::~Support() {}

void Support::send_message(Message* message) {
    switch (message->type) {
    case Message::Type::SELECT:
        if (this == message->select.who_to_select) {
            this->make_selected();
        }
        break;

    case Message::Type::UNSELECT:
        if (this == message->select.who_to_select) {
            this->make_unselected();
            for (auto unit : *this->targets) {
                if (this == unit) continue;
                unit->cell->set_color(CELL_FILL_COLOR);
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

void Support::switch_mode() {
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
void Support::action(sf::Vector2i const& point) {
    
}

