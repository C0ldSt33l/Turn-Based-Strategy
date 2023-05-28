#include "Unit.h"
#include "Map.h"
#include "Manager.h"
#include "DMG_Dealer.h"


Unit* Unit::celected_unit = nullptr;

Unit::Unit() : Drawable(), id(Unit::generate_id()), cell(nullptr) {}
Unit::Unit(sf::Texture const& texture, Cell* cell, int health) :
    Drawable(), id(generate_id()), cell_number(cell->get_number()), HP(health), maxHP(health),
    texture(texture), status(Unit::Status::NONE) {
    this->sprite = Unit::set_sprite(this->texture, cell->get_position());
    
    cell->unit = this;
    cell->has_object = true;
    this->cell = cell;
    
    this->future_sprite = this->sprite;
    this->future_sprite.setColor(SEMI_TRANSPARENT_COLOR);

    this->is_selected = false;
}
Unit::Unit(std::string const file, Cell* cell, int health) :
    Drawable(), id(generate_id()), cell_number(cell->get_number()), HP(health), maxHP(health),
    status(Status::NONE) {
    this->texture.loadFromFile(file);
    this->sprite = Unit::set_sprite(this->texture, cell->get_position());
    
    cell->unit = this;
    cell->has_object = true;
    this->cell = cell;

    this->future_sprite = this->sprite;
    this->future_sprite.setColor(SEMI_TRANSPARENT_COLOR);

    this->is_selected = false;
}
Unit::Unit(Unit const& unit) :
    sf::Drawable(), id(Unit::generate_id()), HP(unit.HP), maxHP(unit.maxHP), cell_number(unit.cell_number),
    texture(unit.texture), sprite(unit.sprite), status(unit.status) , is_selected(unit.is_selected){
    this->sprite.setTexture(this->texture);
}
Unit::~Unit() {

}
Unit& Unit::operator=(Unit const& unit) {
    this->texture = unit.texture;
    this->sprite = unit.sprite;
    this->sprite.setTexture(this->texture);

    return *this;
}

void Unit::set_position(sf::Vector2f const& position) {
    this->sprite.setPosition(position);
}
void Unit::set_position(int x, int y) {
    this->sprite.setPosition(x, y);
}
void Unit::set_position(Cell& cell) {
    this->cell->make_empty();

    this->cell = &cell;
    this->cell->has_object = true;
    
    this->cell_number = cell.get_number();
    this->sprite.setPosition(cell.get_position());
}
void Unit::set_cellNumber(sf::Uint16 number) {
    this->cell_number = number;
}
void Unit::set_status(Status status) {
    this->status = status;
}
void Unit::set_texture(sf::Texture const&) {
    this->texture = texture;
}
void Unit::set_sprite_color(sf::Color const& color) {
    this->sprite.setColor(color);
}
void Unit::set_selected_unit(sf::Vector2i const& point) {
    if (this->cell->contains(point)) {
        this->celected_unit = this;
    }
}

sf::Vector2f Unit::get_position() const {
    return this->sprite.getPosition();
}
int Unit::get_cellNumber() const {
    return this->cell_number;
}
Unit::Status Unit::get_status() const {
    return this->status;
}
sf::Uint16 Unit::get_id() const {
    return this->id;
}
sf::Texture Unit::get_texture() const {
    return this->texture;
}

void Unit::update(sf::RenderWindow const& window, sf::Event const& event) {
    if (Unit::celected_unit && !this->is_selected) {
        return;
    }

    if (event.mouseButton.button == sf::Mouse::Left) {
        this->set_selected_unit(sf::Mouse::getPosition(window));
    }

}

void Unit::move_by_mouse(sf::Mouse::Button const& button, sf::Vector2i const& point) {
    //if (button != sf::Mouse::Left) return;
    
    for (sf::Uint8 i = 0; i < map::CELL_COUNT; i++) {
        if (map::Map::get_instance()[i].contains(point) && map::Map::get_instance()[i].is_empty()) {
            if (button == sf::Mouse::Left) {
                this->set_position(map::Map::get_instance()[i]);
            }
            
            this->future_sprite.setPosition(map::Map::get_instance()[i].get_position());
        }
    }
}
void Unit::move_by_keyboard( sf::Keyboard::Key const& key) {
    sf::Uint8 col = this->cell_number % map::MAP_SIZE.x,
              row = this->cell_number / map::MAP_SIZE.x;
    sf::Uint8 new_cell = this->cell_number;

    switch (key) {
    case sf::Keyboard::W:
    case sf::Keyboard::Up:
        new_cell = --row < 255 ? this->cell_number - map::MAP_SIZE.x : this->cell_number;
        break;

    case sf::Keyboard::S:
    case sf::Keyboard::Down:
        new_cell = ++row < map::MAP_SIZE.y ? this->cell_number + map::MAP_SIZE.x : this->cell_number;
        break;

    case sf::Keyboard::A:
    case sf::Keyboard::Left:
        new_cell = --col < 255 ? this->cell_number - 1 : this->cell_number;
        break;

    case sf::Keyboard::D:
    case sf::Keyboard::Right:
        new_cell = ++col < map::MAP_SIZE.x ? this->cell_number + 1 : this->cell_number;
        break;
  
    default:
        break;
    }

    if (map::Map::get_instance()[new_cell].is_empty()) {
        if (key == sf::Keyboard::Space) {
            this->set_position(map::Map::get_instance()[new_cell]);
        }

        this->future_sprite.setPosition(map::Map::get_instance()[new_cell].get_position());
    }
}

void Unit::take_damage(Unit* attacker, sf::Uint16 damage) {
    this->HP -= damage;

    if (this->HP <= 0) {
        std::cout << "Unit with id<" << this->id << "> is dead\n";
        
        Message* message = new Message;
        message->sender = this;
        message->set_kill(attacker, this);
        Manager::get_instance().send_messange(message);
    }
}
void Unit::take_heal(Unit* healer, sf::Uint16 heal) {
    this->HP = this->HP + heal > this->maxHP ? this->maxHP : this->HP + heal;
}

// STATIC FUNCTIONS
sf::Uint16 Unit::generate_id() {
    static sf::Uint16 new_id = 0;
    return new_id++;
}

void Unit::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(this->future_sprite);
    target.draw(this->sprite);
}

sf::Sprite Unit::set_sprite(sf::Texture const& texture, sf::Vector2f const& pos) {
    sf::Sprite sprite(texture);
    sprite.setOrigin((sf::Vector2f)texture.getSize() / 2.0f);
    sprite.setScale(map::CELL_SIZE.x / (float)texture.getSize().x,
                    map::CELL_SIZE.y / (float)texture.getSize().y);
    sprite.setPosition(pos);

    return sprite;
}
