#pragma once
#include"Unit.h"


class Warrior : public Unit {
private:
    int damege;

public:
    Warrior();
    Warrior(Warrior const& warrior);
    ~Warrior();
};

