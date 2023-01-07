#include "Map.h"

Map::Map::Map(sf::Vector2i size) : size(size.x, size.y) {
    int x = START_POS.x,
        y = START_POS.y;

    sf::RectangleShape rect(sf::Vector2f(CELL_SIZE, CELL_SIZE));
    rect.setFillColor(sf::Color::Green);
    rect.setOrigin(rect.getSize().x / 2, rect.getSize().y / 2);
    rect.setOutlineThickness(5);
    rect.setOutlineColor(sf::Color(23, 56, 190));

    int totalSize = size.x * size.y;
    for (int i = 0; i < totalSize;) {
        rect.setPosition(x, y);
        cells.push_back(rect);
        
        i++;
        x += rect.getSize().x + rect.getOutlineThickness();
        if (!(i % size.x)) {
            x = START_POS.x;
            y += rect.getSize().y + rect.getOutlineThickness();
        }
    }
}

Map::Map::~Map() {
    cells.clear();
}

void Map::Map::draw(sf::RenderWindow& window) {
    for (auto cell : cells) {
        window.draw(cell);
    }
}
