#pragma once
#include"Unit.h"


class Wizard : public Unit {
public:
    Wizard();
    Wizard(Wizard const& wizard);
    ~Wizard();
};

