#pragma once
#include<vector>

#include"Unit.h"


class Unit;

class TargetSelect {
private:
    std::vector<Unit*> targets;

public:
    TargetSelect();
    TargetSelect(TargetSelect& const targerSelect);
    ~TargetSelect();
};

