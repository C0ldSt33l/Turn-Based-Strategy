#pragma once

#include "DMG_Dealer.h"


class Single_DMG_Dealer : public DMG_Dealer {
public:
    Single_DMG_Dealer(Cell* cell, std::list<Unit*>* targets);
	~Single_DMG_Dealer();

	void action(sf::Vector2i const& point);
};

