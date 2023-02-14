#include "Unit.h"
#include "Map.h"


Unit::Unit(sf::Texture& const texture, int health) :
    Drawable(), ID(generateId()), HP(health), maxHP(health), texture(texture), sprite(texture), status(Status::NONE) {
    sprite.setOrigin(texture.getSize().x / 2,
                     texture.getSize().y / 2);
    sprite.setScale(Map::CELL_SIZE.x / (float)texture.getSize().x,
                    Map::CELL_SIZE.y / (float)texture.getSize().y);
}

Unit::Unit(std::string& const file, int health) :
    Drawable(), ID(generateId()), HP(health), maxHP(health), status(Status::NONE) {
    texture.loadFromFile(file);
    sprite.setTexture(texture);
    sprite.setOrigin(texture.getSize().x / 2,
                     texture.getSize().y / 2);
    sprite.setScale(Map::CELL_SIZE.x / (float)texture.getSize().x,
                    Map::CELL_SIZE.y / (float)texture.getSize().y);
}

Unit::Unit(Unit& const unit) :
    sf::Drawable(), ID(generateId()), HP(unit.HP), maxHP(unit.maxHP), cellNumber(unit.cellNumber), sprite(unit.sprite), status(unit.status) {
}

Unit::~Unit() {

}

void Unit::setPosition(sf::Vector2f position) {
    sprite.setPosition(position);
}

void Unit::setPosition(int x, int y) {
    sprite.setPosition(x, y);
}

void Unit::setCellNumber(int number) {
    cellNumber = number;
}

void Unit::setStatus(Status status) {
    this->status = status;
}

sf::Vector2f Unit::getPosition() {
    return sprite.getPosition();
}

int Unit::getCellNumber() {
    return cellNumber;
}

Unit::Status Unit::getStatus() {
    return status;
}

int Unit::getId() {
    static int id = -1;
    return ++id;
}

void Unit::moveByMouse(Map::Map const& map, sf::Mouse::Button button, sf::Vector2i const& point) {
    if (button != sf::Mouse::Left) return;
    
    for (sf::Uint8 i = 0; i < Map::CELL_COUNT; i++) {
        if (map[i].contains(point)) {
            sprite.setPosition(map[i].getPosition());
            cellNumber = i;
        }
    }
}

void Unit::moveByKeyboard(Map::Map const& map, sf::Keyboard::Key key) {
    sf::Uint8 col = cellNumber % Map::MAP_SIZE.x,
              row = cellNumber / Map::MAP_SIZE.x;

    switch (key) {
    case sf::Keyboard::W:
        cellNumber = --row < 255 ? cellNumber - Map::MAP_SIZE.x : cellNumber;
        break;
    case sf::Keyboard::S:
        cellNumber = ++row < Map::MAP_SIZE.y ? cellNumber + Map::MAP_SIZE.x : cellNumber;
        break;
    case sf::Keyboard::A:
        cellNumber = --col < 255 ? --cellNumber : cellNumber;
        break;
    case sf::Keyboard::D:
        cellNumber = ++col < Map::MAP_SIZE.x ? ++cellNumber : cellNumber;
        break;
    default:
        break;
    }

    sprite.setPosition(map[cellNumber].getPosition());
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