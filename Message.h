#pragma once

#include "Unit.h"
#include "Cell.h"


struct Message {
    enum class Type {
        CREATE,
        KILL,
        NEXT_TURN,

        SELECT,
        UNSELECT,

        SWITCH_MODE,
        MOVE,
        //ATTACK,
        DEAL_DMG,
        HEAL,
        BUFF,
        DEBUFF,
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
            Unit* who_to_move;
            Cell* destination;
        } move;
        struct {
            sf::Uint16 damage;
            Unit* attacker;
            Unit* who_to_attack;
        } take_dmg;
        struct {
            sf::Uint16 heal;
            Unit* healer;
            Unit* who_to_heal;
        } heal;
        struct {
            Unit* buffer;
            Unit* who_to_buff;
        } action;
        struct {
            Unit* who_to_select;
        } select;
    };

    Message();

    void set_create(Unit* new_unit);
    void set_kill(Unit* killer, Unit* who_to_kill);
    void set_move(Unit* unit, Cell* cell);
    void set_deal_dmg(Unit* attacker, Unit* who_to_attack, sf::Uint16 damage);
    void set_heal(sf::Uint16 heal, Unit* healer, Unit* who_to_heal);
    void set_buff(Unit* buffer, Unit* who_to_buff);
    void set_select(Unit* who_to_select);
};

