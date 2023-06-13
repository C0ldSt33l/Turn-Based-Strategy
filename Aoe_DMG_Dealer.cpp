#include "Aoe_DMG_Dealer.h"
#include "Manager.h"


Aoe_DMG_Dealer::Aoe_DMG_Dealer(Cell* cell, std::list<Unit*>* targets) : 
    DMG_Dealer("texture//texture.png", 50, cell, targets, Available_Zone::Type::RECT) {}
Aoe_DMG_Dealer::~Aoe_DMG_Dealer() {}

void Aoe_DMG_Dealer::action(sf::Vector2i const& point) {
    if (!this->has_action_point) return;

    Message* msg;
    for (auto cell : this->attack_zone.get_zone()) {
        if (cell && cell->unit) {
            msg = new Message;
            msg->sender = this;
            msg->set_deal_dmg(this, cell->unit, this->damage);
            Manager::get_instance().send_messange(msg);
        }
    }

    this->has_action_point = false;
    for (auto cell : this->attack_zone.get_zone()) {
        if (!cell) continue;
        cell->set_color(CELL_FILL_COLOR);
    }
}
