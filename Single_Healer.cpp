#include "Single_Healer.h"
#include "Manager.h"


Single_Healer::Single_Healer(Cell* cell, std::list<Unit*>* targets) : Healer("textures//hakumen.png", 50, cell, targets) {}
Single_Healer::~Single_Healer() {}

void Single_Healer::action(sf::Vector2i const& point) {
    if (!this->has_action_point) return;

    for (auto unit : *this->targets) {
        if (this == unit) continue;

        if (unit->cell->contains(point) && this->is_target(unit)) {
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
