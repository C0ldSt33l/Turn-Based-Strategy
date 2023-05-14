#include <SFML/Graphics/RenderWindow.hpp>

#include "Cell.h"
#include "Map.h"


Cell::Cell(sf::Vector2f size) :
    sf::Drawable(), hasObject(false), rect(size) {
    static int number = 0;
    this->number = number++;

    this->rect.setFillColor(sf::Color::Green);
    this->rect.setOrigin(rect.getSize().x / 2, rect.getSize().y / 2);
    this->rect.setOutlineThickness(Map::CELL_OUTLINE_THICKNESS);
    this->rect.setOutlineColor(sf::Color(23, 56, 1950));
}
Cell::~Cell() {
}

void Cell::setStatus(bool hasObject) {
    this->hasObject = hasObject;
}
void Cell::setNumber(int number) {
    this->number = number;
}
void Cell::setPosition(sf::Vector2f position) {
    rect.setPosition(position);
}
void Cell::setPosition(int x, int y) {
    rect.setPosition(x, y);
}

bool Cell::isEmpty() const {
    return !hasObject;
}
int Cell::getNumber() const {
    return number;
}
sf::Vector2f Cell::getPosition() const {
    return rect.getPosition();
}
sf::Vector2f Cell::getSize() const {
    return rect.getSize();
}
float Cell::getOutlineThickness() const {
    return rect.getOutlineThickness();
}

bool Cell::contains(sf::Vector2f const& point) const {
    return rect.getGlobalBounds().contains(point);
}
bool Cell::contains(sf::Vector2i const& point) const {
    return rect.getGlobalBounds().contains(sf::Vector2f(point));
}

void Cell::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(rect);
}