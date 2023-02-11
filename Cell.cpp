#include<SFML/Graphics/RenderWindow.hpp>

#include "Cell.h"
#include "Map.h"


Cell::Cell(sf::Vector2f size) :
    sf::Drawable(), number(0), hasObject(false), rect(size) {
    rect.setFillColor(sf::Color::Green);
    rect.setOrigin(rect.getSize().x / 2, rect.getSize().y / 2);
    rect.setOutlineThickness(5);
    rect.setOutlineColor(sf::Color(23, 56, 1950));
}

Cell::Cell(float width, float height) :
    sf::Drawable(), number(0), hasObject(false), rect(sf::Vector2f(width, height)) {
    rect.setFillColor(sf::Color::Green);
    rect.setOrigin(rect.getSize().x / 2, rect.getSize().y / 2);
    rect.setOutlineThickness(5);
    rect.setOutlineColor(sf::Color(23, 56, 1950));
}

Cell::Cell(Cell const& cell) :
    sf::Drawable(), number(cell.number), hasObject(cell.hasObject), rect(cell.rect) {
}

Cell::~Cell() {
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

bool Cell::isEmpty(){
    return hasObject;
}

int Cell::getNumber() {
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

void Cell::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(rect);
}