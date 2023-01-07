#pragma once

#include"Unit.h"


class Support : public Unit {
private:
    int heal;

public:
    Support(int heal = 10);
    Support(Support const& support);
    ~Support();

    void action(Unit* target, int heal);
};