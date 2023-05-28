#pragma once

#include"Unit.h"


class Support : public Unit {
protected:
    int heal;

public:
    Support(int heal = 10);
    Support(Support const& support);
    virtual ~Support();

    void action(Unit* target, int heal);
};