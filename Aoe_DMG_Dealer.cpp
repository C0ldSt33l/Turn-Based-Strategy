#include "Aoe_DMG_Dealer.h"


Aoe_DMG_Dealer::Aoe_DMG_Dealer(Cell* cell, std::list<Unit*>* targets) : 
    DMG_Dealer("texture//texture.png", 50, cell, targets, Available_Zone::Type::RECT) {}
Aoe_DMG_Dealer::~Aoe_DMG_Dealer() {}

void Aoe_DMG_Dealer::action(sf::Vector2i const& point) {

}
