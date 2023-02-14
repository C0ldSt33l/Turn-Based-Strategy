#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>

#include"Unit.h"
#include"TargetSelect.h"
#include"Message.h"
#include"Map.h"

// TODO:
// change generateId();
// implement targetSelect

class targetSelect;

class Unit : public sf::Drawable {
protected:
    int ID;
    int maxHP,
        HP;
    int cellNumber;
    sf::Texture texture;
    sf::Sprite sprite;

    enum class Status {
        NONE,
        STUN,
        POISON,
        HIDDEN
    };
    Status status;

public:
    Unit(sf::Texture& const texture, int health = 100);
    Unit(std::string& const file, int health = 100);
    Unit(Unit& const unit);
    ~Unit();

    void setPosition(sf::Vector2f position);
    void setPosition(int x, int y);
    void setCellNumber(int number);
    void setStatus(Status status);

    int getId();
    sf::Vector2f getPosition();
    int getCellNumber();
    Status getStatus();

    //void update() = 0;
    //void sendMessage(Message& const messege) = 0;

    void moveByMouse(Map::Map const& map, sf::Mouse::Button button, sf::Vector2i const& point);
    void moveByKeyboard(Map::Map const& map, sf::Keyboard::Key key);

    void takeDamage(int damage);
    void takeHeal(int heal);

private:
    static int generateId();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};