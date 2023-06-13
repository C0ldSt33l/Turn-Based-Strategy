#include "Healer.h"
#include "Manager.h"


Healer::~Healer() {}

sf::Uint16 Healer::get_heal() const {
    return this->heal;
}
