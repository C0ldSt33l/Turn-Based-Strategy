#pragma once
class Turn {
    enum class Team {
        PLAYER,
        ENEMY,
    };

    Team team;

public:
    void next();

    void select_unit();
};

