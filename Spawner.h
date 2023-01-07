#pragma once
#include<vector>

#include"Unit.h"


class Spawner {
private:
    std::vector<Unit*> Allies;
    std::vector<Unit*> Enemines;

public:
    void add(int type, int side);
    void del(int number);

    void spawn(int number);
    void spawn();

    void clear();
};

