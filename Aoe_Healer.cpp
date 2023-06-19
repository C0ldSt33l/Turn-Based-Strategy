#include "Aoe_Healer.h"
#include "Manager.h"

Aoe_Healer::Aoe_Healer(const std::string file, const Unit::Team team, Cell* cell, std::list<Unit*>* targets) :
    Healer(file, 10, cell, targets) {
    this->team = team;
}
Aoe_Healer::~Aoe_Healer() {}

void Aoe_Healer::action(sf::Vector2i const& point) {
    if (!this->has_action_point) return;

    Message* msg;
    for (auto unit : *this->targets) {
        msg = new Message;
        msg->sender = this;
        msg->set_heal(this->heal, this, unit);
        Manager::get_instance().send_messange(msg);
    }
    this->has_action_point = false;

    for (auto unit : *this->targets) {
        if (this == unit) continue;
        unit->cell->set_color(CELL_FILL_COLOR);
    }
}
