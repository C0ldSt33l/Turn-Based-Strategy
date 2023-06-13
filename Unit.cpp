#include "Unit.h"
#include "Map.h"
#include "Manager.h"
#include "DMG_Dealer.h"


sf::Clock Unit::input_colddown;
Unit*     Unit::celected_unit = nullptr;

Unit::Unit(std::string const file, sf::Int32 health, std::list<Unit*>* targets, Available_Zone::Type move_zone) :
    Drawable(), id(generate_id()), cell(nullptr), targets(targets), cur_hp(health), max_hp(health), status(Status::NONE),
    move_zone(cell, move_zone) {
    if (!this->texture.loadFromFile(file)) {
        exit(1);
    }
    this->sprite = Unit::set_sprite(this->texture, sf::Vector2f()/*cell->get_position()*/);

    this->projection = this->sprite;
    this->projection.setColor(SEMI_TRANSPARENT_COLOR);

    this->action_mode = Unit::Mode::MOVING;
    this->has_action_point = this->has_move_point = true;
}
Unit::Unit(Unit const& unit) :
    sf::Drawable(), id(Unit::generate_id()), cur_hp(unit.cur_hp), max_hp(unit.max_hp), texture(unit.texture),
    sprite(unit.sprite), status(unit.status) {
    this->sprite.setTexture(this->texture);
}
Unit::~Unit() {
    this->cell->unit = nullptr;
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
void Unit::set_status(Status status) {
    this->status = status;
}
void Unit::set_texture(sf::Texture const&) {
    this->texture = texture;
}
void Unit::set_sprite_color(sf::Color const& color) {
    this->sprite.setColor(color);
}
void Unit::make_selected() {
    this->celected_unit = this;
    this->celected_unit->set_sprite_color(SELECT_COLOR);

    for (auto cell : this->move_zone.get_zone()) {
        if (!cell || cell == this->cell) continue;
        cell->set_color(SEMI_TRANSPARENT_COLOR);
    }
}
void Unit::make_unselected() {
    Unit::celected_unit->action_mode = Unit::Mode::MOVING;
    Unit::celected_unit->has_action_point = Unit::celected_unit->has_move_point = true;
    
    Unit::celected_unit->set_sprite_color(DEFAULT_COLOR);
    Unit::celected_unit->projection.setPosition(Unit::celected_unit->sprite.getPosition());
    
    Unit::celected_unit = nullptr;
}

sf::Uint16 Unit::get_id() const {
    return this->id;
}
sf::Int32 Unit::get_hp() const {
    return this->cur_hp;
}
sf::Vector2f Unit::get_position() const {
    return this->sprite.getPosition();
}
Unit::Status Unit::get_status() const {
    return this->status;
}
sf::Texture Unit::get_texture() const {
    return this->texture;
}

void Unit::move_to(Cell* cell) {
    for (auto cell : this->move_zone.get_zone()) {
        if (!cell || cell == this->cell) continue;
        cell->set_color(CELL_FILL_COLOR);
    }

    if (this->cell) this->cell->make_empty();
    this->cell = cell;
    this->cell->unit = this;

    this->sprite.setPosition(cell->get_position());
    this->projection.setPosition(cell->get_position());

    this->move_zone.update(cell);
}
void Unit::move_by_mouse(sf::Mouse::Button const& button, sf::Vector2i const& point) {
    if (!this->has_move_point) return;

    for (sf::Uint8 i = 0; i < map::CELL_COUNT; ++i) {
        if (map::Map::get_instance()[i].is_empty() && map::Map::get_instance()[i].in_available_zone(this->move_zone.get_zone()) && map::Map::get_instance()[i].contains(point)) {
            if (button == sf::Mouse::Left) {
                this->has_move_point = false;

                Message* msg = new Message;
                msg->sender = this;
                msg->set_move(this, &map::Map::get_instance()[i]);
                Manager::get_instance().send_messange(msg);
            }
            
            this->projection.setPosition(map::Map::get_instance()[i].get_position());
        }
    }
}
void Unit::move_by_keyboard(sf::Keyboard::Key const& key) {
    sf::Uint8 col = this->cell->number % map::MAP_SIZE.x,
              row = this->cell->number / map::MAP_SIZE.x;
    sf::Uint8 new_cell = this->cell->number;

    switch (key) {
    case sf::Keyboard::W:
    case sf::Keyboard::Up:
        new_cell = --row < 255 ? this->cell->number - map::MAP_SIZE.x : this->cell->number;
        break;

    case sf::Keyboard::S:
    case sf::Keyboard::Down:
        new_cell = ++row < map::MAP_SIZE.y ? this->cell->number + map::MAP_SIZE.x : this->cell->number;
        break;

    case sf::Keyboard::A:
    case sf::Keyboard::Left:
        new_cell = --col < 255 ? this->cell->number - 1 : this->cell->number;
        break;

    case sf::Keyboard::D:
    case sf::Keyboard::Right:
        new_cell = ++col < map::MAP_SIZE.x ? this->cell->number + 1 : this->cell->number;
        break;
  
    default:
        break;
    }

    if (map::Map::get_instance()[new_cell].is_empty()) {
        if (key == sf::Keyboard::Space) {
            this->move_to(&map::Map::get_instance()[new_cell]);
        }

        this->projection.setPosition(map::Map::get_instance()[new_cell].get_position());
    }
}
void Unit::move_projection(Cell const* cell) {
    this->projection.setPosition(cell->get_position());
}

void Unit::take_damage(Unit* attacker, sf::Uint16 damage) {
    this->cur_hp -= damage;

    if (this->cur_hp <= 0) {
        std::cout << "Unit with id<" << this->id << "> is dead\n";
        
        Message* message = new Message;
        message->sender = this;
        message->set_kill(attacker, this);
        Manager::get_instance().send_messange(message);
    }
}
void Unit::take_heal(Unit* healer, sf::Uint16 heal) {
    this->cur_hp = this->cur_hp + heal >= this->max_hp ? this->max_hp : this->cur_hp + heal;
}

// STATIC METHODS
sf::Uint16 Unit::generate_id() {
    static sf::Uint16 new_id = 0;
    return new_id++;
}
Unit* Unit::get_selected_unit() {
    return Unit::celected_unit;
}
sf::Sprite Unit::set_sprite(sf::Texture const& texture, sf::Vector2f const& pos) {
    sf::Sprite sprite(texture);
    sprite.setOrigin((sf::Vector2f)texture.getSize() / 2.0f);
    sprite.setScale(map::CELL_SIZE.x / (float)texture.getSize().x,
                    map::CELL_SIZE.y / (float)texture.getSize().y);
    //sprite.setPosition(pos);

    return sprite;
}

void Unit::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(this->projection);
    target.draw(this->sprite);
}