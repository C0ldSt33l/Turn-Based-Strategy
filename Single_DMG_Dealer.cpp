#include "Single_DMG_Dealer.h"
#include "Manager.h"


Single_DMG_Dealer::Single_DMG_Dealer(const Unit::Team team, Cell* cell, std::list<Unit*>* targets) :
    DMG_Dealer("textures//naoto.png", 50, cell, targets, Available_Zone::Type::LINE) {
    this->team = team;
}
Single_DMG_Dealer::~Single_DMG_Dealer() {}

void Single_DMG_Dealer::action(sf::Vector2i const& point) {
    if (!this->has_action_point) return;

    for (auto cell : this->attack_zone.get_zone()) {
        if (cell && cell->contains(point)) {
            this->has_action_point = this->has_move_point = false;
            for (auto cell : this->attack_zone.get_zone()) {
                if (!cell) continue;
                cell->set_color(CELL_FILL_COLOR);
            }

            if (cell->unit && this->is_target(cell->unit)) {
                Message* msg = new Message;
                msg->sender = this;
                msg->set_deal_dmg(this, cell->unit, this->damage);
                Manager::get_instance().send_messange(msg);
            }

            break;
        }
    }
}
