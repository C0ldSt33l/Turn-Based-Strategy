#include "Unit.h"


Unit::Unit(sf::Texture& const texture, int health) : health(health), Sprite(texture) {
    this->setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
    this->scale(Map::CELL_SIZE / this->getTextureRect().width,
                Map::CELL_SIZE / this->getTextureRect().height);
}

Unit::Unit(Unit& const unit) : Sprite(unit) {
    health = unit.health;
    status = unit.status;
}

Unit::~Unit() {
    //if (target) delete target;
}

void Unit::takeDamage(int damage) {
    health -= damage;

    if (0 >= health)
        std::cout << "Unit is killed" << std::endl;
}

void Unit::draw(sf::RenderTarget& target) const {
    target.draw(*this);
}
