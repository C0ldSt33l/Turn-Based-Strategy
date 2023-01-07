#pragma once
#include"Unit.h"


class Warrior : public Unit {
public:
    Warrior();
    Warrior(Warrior const& warrior);
    ~Warrior();
};

