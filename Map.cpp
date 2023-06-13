#include <iostream>

#include "Map.h"


map::Map::Map(sf::Vector2i size) : sf::Drawable(), size(size.x, size.y) {
    int x = START_POS.x,
        y = START_POS.y;

    Cell tmp(CELL_SIZE);

    int totalSize = size.x * size.y;
    for (int i = 1; i <= totalSize; i++) {
        tmp.set_number(i - 1);
        tmp.set_position(x, y);
        this->cells.push_back(tmp);

        x += tmp.get_size().x + tmp.get_outline_thickness();
        if (!(i % size.x)) {
            x = START_POS.x;
            y += tmp.get_size().y + tmp.get_outline_thickness();
        }
    }
}
map::Map::~Map() {
    cells.clear();
}

map::Map& map::Map::get_instance() {
    static Map instance;
    return instance;
}

void map::Map::draw_unit_position() const {
    for (sf::Uint16 i = 0; i < CELL_COUNT; i++) {
        if (!(i % MAP_SIZE.x)) {
            std::cout << '\n';
        }
        std::cout << (this->cells[i].is_empty() ? "E" : "U");
    }

    system("cls");
}

Cell& map::Map::operator[](sf::Uint16 i) {
    return cells[i];
}
Cell const& map::Map::get_cell(sf::Uint16 i) const {
    return this->cells[i];
}

void map::Map::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (auto cell : cells) {
        target.draw(cell);
    }
}

void map::Map::load_from_file(std::string const& file) {
}
