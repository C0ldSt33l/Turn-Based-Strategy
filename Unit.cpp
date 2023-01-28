#include "Unit.h"
#include "Map.h"


Unit::Unit(sf::Texture& const texture, int health) :
    Drawable(),
    ID(generateId()),
    HP(health),
    maxHP(health),
    texture(texture),
    sprite(texture),
    status(Status::NONE) {
    sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
    sprite.setScale(Map::CELL_SIZE / (float)texture.getSize().x,
                    Map::CELL_SIZE / (float)texture.getSize().y);
}

Unit::Unit(std::string& const file, int health) :
    Drawable(),
    ID(generateId()),
    HP(health),
    maxHP(health),
    status(Status::NONE) {
    sf::Texture tmp;
    tmp.loadFromFile(file);

    texture = tmp;
    sprite.setTexture(texture);
    sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
    sprite.setScale(Map::CELL_SIZE / (float)texture.getSize().x,
        Map::CELL_SIZE / (float)texture.getSize().y);
}

Unit::Unit(Unit& const unit) :
    sf::Drawable(),
    ID(generateId()),
    position(unit.position),
    HP(unit.HP),
    maxHP(unit.maxHP),
    sprite(unit.sprite),
    status(unit.status)
{}

Unit::~Unit() {

}

void Unit::setPosition(sf::Vector2f position) {
    this->position = position;
    sprite.setPosition(position);
}

void Unit::setPosition(int x, int y) {
    position.x = x;
    position.y = y;
    sprite.setPosition(x, y);
}

void Unit::setStatus(Status status) {
    this->status = status;
}

sf::Vector2f Unit::getPosition() {
    return position;
}

Unit::Status Unit::getStatus() {
    return status;
}

int Unit::getId() {
    static int id = -1;
    return ++id;
}

void Unit::takeDamage(int damage) {
    HP = HP - damage < 0 ? 0 : HP - damage;

    if (!HP) {
        std::cout << "Unit is dead\n";
    }
}

void Unit::takeHeal(int heal) {
    HP = HP + heal > maxHP ? maxHP : HP + heal;
}

int Unit::generateId() {
    return 0;
}

void Unit::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite);
}