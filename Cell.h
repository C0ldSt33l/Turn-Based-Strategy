#pragma once
#include<SFML/Graphics.hpp>


class Cell : public sf::RectangleShape {
    bool hasObject;
    sf::Sprite sprite;

public:
    Cell();
    Cell(Cell& const cell);
    virtual ~Cell();

    bool isEmpty();

    void draw(sf::RenderWindow& window);
};

