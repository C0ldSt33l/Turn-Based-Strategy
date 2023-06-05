#include "Unit.h"
#include "Map.h"
#include "Manager.h"
#include "DMG_Dealer.h"


Unit* Unit::celected_unit = nullptr;

sf::Clock Unit::input_colddown;

Unit::Unit() : Drawable(), id(Unit::generate_id()), cell(nullptr), cur_hp(100), max_hp(100) {}
Unit::Unit(sf::Texture const& texture, Cell* cell, int health) :
    Drawable(), id(generate_id()), cur_hp(health), max_hp(health),
    texture(texture), status(Unit::Status::NONE) {
    this->sprite = Unit::set_sprite(this->texture, cell->get_position());

    cell->unit = this;
    cell->has_object = true;
    this->cell = cell;
    
    this->future_sprite = this->sprite;
    this->future_sprite.setColor(SEMI_TRANSPARENT_COLOR);
}
Unit::Unit(std::string const file, Cell* cell, int health) :
    Drawable(), id(generate_id()), cur_hp(health), max_hp(health), status(Status::NONE), move_zone(cell, Available_Zone::Type::AROUND) {
    this->texture.loadFromFile(file);
    this->sprite = Unit::set_sprite(this->texture, cell->get_position());
    
    cell->unit = this;
    cell->has_object = true;
    this->cell = cell;

    this->future_sprite = this->sprite;
    this->future_sprite.setColor(SEMI_TRANSPARENT_COLOR);
}
Unit::Unit(Unit const& unit) :
    sf::Drawable(), id(Unit::generate_id()), cur_hp(unit.cur_hp), max_hp(unit.max_hp), texture(unit.texture),
    sprite(unit.sprite), status(unit.status) {
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
}
void Unit::make_unselected() {
    this->celected_unit->set_sprite_color(DEFAULT_COLOR);
    this->celected_unit = nullptr;
}

sf::Vector2f Unit::get_position() const {
    return this->sprite.getPosition();
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
Unit* Unit::get_selected_unit() {
    return this->celected_unit;
}

void Unit::update(sf::RenderWindow const& window, sf::Event const& event) {
    if (!Unit::celected_unit && this->input_colddown.getElapsedTime().asMilliseconds() >= 250) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->cell->contains(sf::Mouse::getPosition(window))) {
            Message* msg = new Message;
            msg->sender = this;
            msg->set_select(this);
            Manager::get_instance().send_messange(msg);
        }

        return;
    }

    if (this == Unit::celected_unit) {
        this->move_by_mouse(event.mouseButton.button, sf::Mouse::getPosition(window));
    }
}
void Unit::send_message(Message* message) {
    switch (message->type) {
    case Message::Type::SELECT:
        if (this == message->select.who_to_select) {
            this->make_selected();
        }
        break;

    case Message::Type::UNSELECT:
        if (this == message->select.who_to_select) {
            this->make_unselected();
        }
        break;

    case Message::Type::ATTACK:
        break;

    case Message::Type::MOVE_UNIT:
        if (this != message->move.who_to_move)
            return;
        this->move_to(message->move.destination);
        break;

    case Message::Type::MOVE_PROJECTION:
        if (this != message->move.who_to_move)
            return;
        this->move_to(message->move.destination);
        break;

    default:
        break;
    }
}

void Unit::move_to(Cell* cell) {
    this->cell->make_empty();

    this->cell = cell;
    this->cell->has_object = true;

    this->sprite.setPosition(cell->get_position());

    this->input_colddown.restart();
}
void Unit::move_by_mouse(sf::Mouse::Button const& button, sf::Vector2i const& point) {
    //if (button != sf::Mouse::Left) return;
    
    for (sf::Uint8 i = 0; i < map::CELL_COUNT; i++) {
        if (map::Map::get_instance()[i].contains(point) && map::Map::get_instance()[i].is_empty()) {
            if (button == sf::Mouse::Left) {
                //this->move_to(&map::Map::get_instance()[i]);
                Message* msg = new Message;
                msg->sender = this;
                msg->set_select(this);
                msg->type = Message::Type::UNSELECT;
                Manager::get_instance().send_messange(msg);

                msg = new Message;
                msg->sender = this;
                msg->set_move(this, &map::Map::get_instance()[i]);
                Manager::get_instance().send_messange(msg);
            }
            
            this->future_sprite.setPosition(map::Map::get_instance()[i].get_position());
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

        this->future_sprite.setPosition(map::Map::get_instance()[new_cell].get_position());
    }
}
void Unit::move_projection(Cell const* cell) {
    this->future_sprite.setPosition(cell->get_position());
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
    this->cur_hp = this->cur_hp + heal > this->max_hp ? this->max_hp : this->cur_hp + heal;
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
