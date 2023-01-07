#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>

#include"Unit.h"
#include"TargetSelect.h"
#include"Message.h"
#include"Map.h"


class TargetSelect;

class Unit : public sf::Sprite {
protected:
    int health;
    //TargetSelect* target{ nullptr };
    enum class Status {
        NONE,
        HIDDING,
        POISON,
        STUN,
        INCREASE_ATTACK,
        DECREASE_ATTACK
    };

    Status status = Status::NONE;
public:
    Unit(sf::Texture& const texture, int health = 100);
    Unit(Unit& const unit);
    virtual ~Unit();

    //virtual void action(Unit* target) = 0;

    //virtual void update() = 0;
    //virtual void sendMessage(Message message) = 0;

    void takeDamage(int damage);

    void draw(sf::RenderTarget& target) const;
};