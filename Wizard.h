#pragma once
#include"Unit.h"


class Wizard : public Unit {
private:
    int damage;

public:
    Wizard();
    Wizard(Wizard const& wizard);
    ~Wizard();
};

