#include "Unit.h"
#include "Map.h"


Unit::Unit(sf::Texture& const texture, Cell& cell, int health) :
    Drawable(), id(generate_id()), cellNumber(cell.getNumber()), HP(health), maxHP(health),
    texture(texture), sprite(texture), status(Status::NONE) {
    this->sprite.setOrigin((sf::Vector2f)this->texture.getSize() / 2.0f);
    this->sprite.setScale(Map::CELL_SIZE.x / (float)this->texture.getSize().x,
                          Map::CELL_SIZE.y / (float)this->texture.getSize().y);
    this->sprite.setPosition(cell.getPosition());
    cell.setStatus(true);
    
    this->future_sprite = this->sprite;
    this->future_sprite.setColor(SEMI_TRANSPARENT_COLOR);
}
Unit::Unit(std::string& const file, Cell& cell, int health) :
    Drawable(), id(generate_id()), cellNumber(cell.getNumber()), HP(health), maxHP(health),
    status(Status::NONE) {
    this->texture.loadFromFile(file);
    
    this->sprite.setTexture(this->texture);
    this->sprite.setOrigin((sf::Vector2f)texture.getSize() / 2.0f);
    this->sprite.setScale(Map::CELL_SIZE.x / (float)this->texture.getSize().x,
                          Map::CELL_SIZE.y / (float)this->texture.getSize().y);
    this->sprite.setPosition(cell.getPosition());
    cell.setStatus(true);

    this->future_sprite = this->sprite;
    this->future_sprite.setColor(SEMI_TRANSPARENT_COLOR);
}
Unit::Unit(Unit& const unit) :
    sf::Drawable(), id(generate_id()), HP(unit.HP), maxHP(unit.maxHP), cellNumber(unit.cellNumber),
    sprite(unit.sprite), status(unit.status) {
}
Unit::~Unit() {

}

void Unit::set_position(sf::Vector2f const& position) {
    this->sprite.setPosition(position);
}
void Unit::set_position(int x, int y) {
    this->sprite.setPosition(x, y);
}
void Unit::set_position(Cell& cell) {
    this->sprite.setPosition(cell.getPosition());
    this->cellNumber = cell.getNumber();

    cell.setStatus(true);
}
void Unit::set_cellNumber(int number) {
    this->cellNumber = number;
}
void Unit::set_status(Status status) {
    this->status = status;
}

sf::Vector2f Unit::get_position() const {
    return this->sprite.getPosition();
}
int Unit::get_cellNumber() const {
    return this->cellNumber;
}
Unit::Status Unit::get_status() const {
    return this->status;
}
int Unit::get_id() const {
    return this->id;
}

void Unit::move_by_mouse(Map::Map& map, sf::Mouse::Button& button, sf::Vector2i const& point) {
    //if (button != sf::Mouse::Left) return;
    
    for (sf::Uint8 i = 0; i < Map::CELL_COUNT; i++) {
        if (map[i].contains(point) && map[i].isEmpty()) {
            if (button == sf::Mouse::Left) {
                map[this->cellNumber].setStatus(false);
                this->set_position(map[i]);
            }
            
            this->future_sprite.setPosition(map[i].getPosition());
        }
    }
}
void Unit::move_by_keyboard(Map::Map& map, sf::Keyboard::Key key) {
    sf::Uint8 col = this->cellNumber % Map::MAP_SIZE.x,
              row = this->cellNumber / Map::MAP_SIZE.x;
    sf::Uint8 new_cell = this->cellNumber;

    switch (key) {
    case sf::Keyboard::Up:
    case sf::Keyboard::W:
        new_cell = --row < 255 ? this->cellNumber - Map::MAP_SIZE.x : this->cellNumber;
        break;

    case sf::Keyboard::Down:
    case sf::Keyboard::S:
        new_cell = ++row < Map::MAP_SIZE.y ? this->cellNumber + Map::MAP_SIZE.x : this->cellNumber;
        break;

    case sf::Keyboard::Left:
    case sf::Keyboard::A:
        new_cell = --col < 255 ? this->cellNumber - 1 : this->cellNumber;
        break;

    case sf::Keyboard::Right:
    case sf::Keyboard::D:
        new_cell = ++col < Map::MAP_SIZE.x ? this->cellNumber + 1 : this->cellNumber;
        break;
  
    default:
        break;
    }

    if (map[new_cell].isEmpty()) {
        if (key == sf::Keyboard::Space) {
            map[this->cellNumber].setStatus(false);
            this->set_position(map[new_cell]);
        }

        this->future_sprite.setPosition(map[new_cell].getPosition());
    }
}

void Unit::take_damage(int damage) {
    this->HP -= damage;

    if (this->HP <= 0) {
        std::cout << "Unit is dead\n";
    }
}
void Unit::take_heal(int heal) {
    this->HP = this->HP + heal > this->maxHP ? this->maxHP : this->HP + heal;
}

sf::Uint32 Unit::generate_id() {
    static sf::Uint32 new_id = 0;
    return new_id++;
}

void Unit::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(this->future_sprite);
    target.draw(this->sprite);
}

int Unit::move() {
    return 0;
}
