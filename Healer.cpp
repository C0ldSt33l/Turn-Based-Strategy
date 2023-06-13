#include "Healer.h"
#include "Manager.h"


Healer::Healer(std::string const file, sf::Uint16 heal, Cell* cell, std::list<Unit*>* targets) :
    Support(file, cell, targets), heal(heal) {}
Healer::~Healer() {}

sf::Uint16 Healer::get_heal() const {
    return this->heal;
}
