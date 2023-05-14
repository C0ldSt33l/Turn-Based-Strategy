#include "Unit.h"
#include "Map.h"


Unit::Unit(sf::Texture& const texture, int health) :
    Drawable(), ID(generateId()), HP(health), maxHP(health), texture(texture),
    sprite(texture), status(Status::NONE) {
    this->sprite.setOrigin((sf::Vector2f)this->texture.getSize() / 2.0f);
    this->sprite.setScale(Map::CELL_SIZE.x / (float)this->texture.getSize().x,
                          Map::CELL_SIZE.y / (float)this->texture.getSize().y);
}

Unit::Unit(std::string& const file, int health) :
    Drawable(), ID(generateId()), HP(health), maxHP(health), status(Status::NONE) {
    this->texture.loadFromFile(file);
    this->sprite.setTexture(this->texture);
    this->sprite.setOrigin((sf::Vector2f)texture.getSize() / 2.0f);
    this->sprite.setScale(Map::CELL_SIZE.x / (float)this->texture.getSize().x,
                          Map::CELL_SIZE.y / (float)this->texture.getSize().y);
}

Unit::Unit(Unit& const unit) :
    sf::Drawable(), ID(generateId()), HP(unit.HP), maxHP(unit.maxHP), cellNumber(unit.cellNumber),
    sprite(unit.sprite), status(unit.status) {
}

Unit::~Unit() {

}

void Unit::setPosition(sf::Vector2f const& position) {
    this->sprite.setPosition(position);
}

void Unit::setPosition(int x, int y) {
    this->sprite.setPosition(x, y);
}

void Unit::setPosition(Cell& cell) {
    this->sprite.setPosition(cell.getPosition());
    this->cellNumber = cell.getNumber();

    cell.setStatus(true);
}

void Unit::setCellNumber(int number) {
    this->cellNumber = number;
}

void Unit::setStatus(Status status) {
    this->status = status;
}

sf::Vector2f Unit::getPosition() {
    return this->sprite.getPosition();
}

int Unit::getCellNumber() {
    return this->cellNumber;
}

Unit::Status Unit::getStatus() {
    return this->status;
}

int Unit::getId() {
    static int id = 0;
    return id++;
}

void Unit::moveByMouse(Map::Map& map, sf::Mouse::Button& button, sf::Vector2i const& point) {
    if (button != sf::Mouse::Left) return;
    
    for (sf::Uint8 i = 0; i < Map::CELL_COUNT; i++) {
        if (map[i].contains(point) && map[i].isEmpty()) {
            map[this->cellNumber].setStatus(false);
            this->setPosition(map[i]);
        }
    }
}

void Unit::moveByKeyboard(Map::Map& map, sf::Keyboard::Key key) {
    sf::Uint8 col = this->cellNumber % Map::MAP_SIZE.x,
              row = this->cellNumber / Map::MAP_SIZE.x;
    sf::Uint8 new_pos;

    switch (key) {
    case sf::Keyboard::Up:
    case sf::Keyboard::W:
        new_pos = --row < 255 ? this->cellNumber - Map::MAP_SIZE.x : this->cellNumber;
        break;

    case sf::Keyboard::Down:
    case sf::Keyboard::S:
        new_pos = ++row < Map::MAP_SIZE.y ? this->cellNumber + Map::MAP_SIZE.x : this->cellNumber;
        break;

    case sf::Keyboard::Left:
    case sf::Keyboard::A:
        new_pos = --col < 255 ? this->cellNumber - 1 : this->cellNumber;
        break;

    case sf::Keyboard::Right:
    case sf::Keyboard::D:
        new_pos = ++col < Map::MAP_SIZE.x ? this->cellNumber + 1 : this->cellNumber;
        break;

    default:
        break;
    }

    if (map[new_pos].isEmpty()) {
        map[this->cellNumber].setStatus(false);
        this->setPosition(map[new_pos]);
    }
}

void Unit::takeDamage(int damage) {
    this->HP -= damage;

    if (this->HP <= 0) {
        std::cout << "Unit is dead\n";
    }
}

void Unit::takeHeal(int heal) {
    this->HP = this->HP + heal > this->maxHP ? this->maxHP : this->HP + heal;
}

int Unit::generateId() {
    static uint32_t new_id = 0;
    return new_id++;
}

void Unit::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(this->sprite);
}