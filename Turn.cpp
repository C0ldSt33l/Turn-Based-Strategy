#include "Turn.h"

void Turn::next() {
    this->team = this->team == Team::PLAYER ?
        Team::ENEMY : Team::PLAYER;
}

void Turn::select_unit() {
}
