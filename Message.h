#pragma once

#include "Unit.h"
#include "Cell.h"


struct Message {
    enum class Type {
        CREATE,
        KILL,
        MOVE,
        MOVE_BY_KEYBOARD,
        MOVE_BY_MOUSE,
        ATTACK,
        HEAL,
        BUFF,
        SELECT
    };
    Message::Type type;
    Unit* sender;
    union {
        struct {
            Unit* new_unit;
        } create;
        struct {
            Unit* killer;
            Unit* who_to_kill;
        } kill;
        struct {
            sf::Event* event;
        } move;
        struct {
            Unit* attacker;
            Unit* who_to_attack;
        } attack;
        struct {
            Unit* healer;
            Unit* who_to_heal;
        } heal;
        struct {
            Unit* buffer;
            Unit* who_to_buff;
        } buff;
        struct {
            Unit* who_select;
        } select;
    };

    Message();

    void set_create(Unit* new_unit);
    void set_kill(Unit* killer, Unit* who_to_kill);
    void set_move(sf::Event* event);
    void set_attack(Unit* attacker, Unit* who_to_attack);
    void set_heal(Unit* healer, Unit* who_to_heal);
    void set_buff(Unit* buffer, Unit* who_to_buff);
    void set_select(Unit* who_to_select);
};

