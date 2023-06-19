#include "Aoe_DMG_Dealer.h"
#include "Manager.h"


Aoe_DMG_Dealer::Aoe_DMG_Dealer(const std::string file, const Unit::Team team, Cell* cell, std::list<Unit*>* targets) :
    DMG_Dealer(file, 50, cell, targets, Available_Zone(Available_Zone::RECT_ZONE)) {
    this->team = team;
}
Aoe_DMG_Dealer::~Aoe_DMG_Dealer() {}

void Aoe_DMG_Dealer::action(sf::Vector2i const& point) {
    if (!this->has_action_point) return;

    bool is_cell_in_zone = false;
    for (auto cell : this->attack_zone.get_zone()) {
        if (cell && cell->contains(point)) {
            is_cell_in_zone = true;
            break;
        }
    }

    if (is_cell_in_zone) {
        this->has_action_point = this->has_move_point = false;
        for (auto cell : this->attack_zone.get_zone()) {
            if (!cell) continue;
            cell->set_color(CELL_FILL_COLOR);
        }

        Message* msg;
        for (auto cell : this->attack_zone.get_zone()) {
            if (cell && cell->unit && this->is_target(cell->unit)) {
                msg = new Message;
                msg->sender = this;
                msg->set_deal_dmg(this, cell->unit, this->damage);
                Manager::get_instance().send_messange(msg);
            }
        }
    }
}
