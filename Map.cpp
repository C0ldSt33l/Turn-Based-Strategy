#include "Map.h"

void Map::Map::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (auto cell : cells) {
        target.draw(cell);
    }
}

Map::Map::Map(sf::Vector2i size) : sf::Drawable(), size(size.x, size.y) {
    int x = START_POS.x,
        y = START_POS.y;

    Cell tmp(CELL_SIZE);

    int totalSize = size.x * size.y;
    for (int i = 1; i <= totalSize; i++) {
        tmp.setNumber(i - 1);
        tmp.setPosition(x, y);
        cells.push_back(tmp);

        x += tmp.getSize().x + tmp.getOutlineThickness();
        if (!(i % size.x)) {
            x = START_POS.x;
            y += tmp.getSize().y + tmp.getOutlineThickness();
        }
    }
}

Map::Map::~Map() {
    cells.clear();
}

Cell Map::Map::operator[](int i) const {
    return cells[i];
}