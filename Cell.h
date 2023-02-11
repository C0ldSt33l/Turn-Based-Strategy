#pragma once
#include<SFML/Graphics.hpp>


class Cell : public sf::Drawable {
    int number;
    bool hasObject;

    sf::RectangleShape rect;
    //sf::Sprite sprite;

public:
    Cell(sf::Vector2f size);
    Cell(float width, float height);
    Cell(Cell const& cell);
    virtual ~Cell();

    void setNumber(int number);
    void setPosition(sf::Vector2f position);
    void setPosition(int x, int y);

    bool isEmpty();
    int getNumber();
    sf::Vector2f getPosition() const;
    sf::Vector2f getSize() const;
    float getOutlineThickness() const;

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

