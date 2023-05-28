#include <SFML/Graphics/RenderWindow.hpp>

#include "Cell.h"
#include "Map.h"


Cell::Cell(sf::Vector2f size) :
    sf::Drawable(), number(Cell::generate_num()), has_object(false), rect(size) {
    this->rect.setFillColor(CELL_FILL_COLOR);
    this->rect.setOrigin(rect.getSize().x / 2, rect.getSize().y / 2);
    this->rect.setOutlineThickness(map::CELL_OUTLINE_THICKNESS);
    this->rect.setOutlineColor(CELL_OUTLINE_COLOR);

    this->unit = nullptr;
}
Cell::~Cell() {
}

void Cell::set_status(bool hasObject) {
    this->has_object = hasObject;
}
void Cell::set_number(int number) {
    this->number = number;
}
void Cell::set_position(sf::Vector2f position) {
    rect.setPosition(position);
}
void Cell::set_position(int x, int y) {
    rect.setPosition(x, y);
}
void Cell::make_empty() {
    this->unit = nullptr;
    this->has_object = false;
}

bool Cell::is_empty() const {
    return !has_object;
}
int Cell::get_number() const {
    return number;
}
sf::Vector2f Cell::get_position() const {
    return rect.getPosition();
}
sf::Vector2f Cell::get_size() const {
    return rect.getSize();
}
float Cell::get_outline_thickness() const {
    return rect.getOutlineThickness();
}

bool Cell::contains(sf::Vector2f const& point) const {
    return rect.getGlobalBounds().contains(point);
}
bool Cell::contains(sf::Vector2i const& point) const {
    return rect.getGlobalBounds().contains(sf::Vector2f(point));
}

sf::Uint16 Cell::generate_num() {
    static sf::Uint16 new_number = 0;
    return new_number++;
}

void Cell::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(rect);
}