#pragma once

#include <SFML/Graphics.hpp>


class Cell : public sf::Drawable {
    enum class Type {
        EATHE,
        WATER,
        WALL,
    };

    int number;
    sf::RectangleShape rect;
    //static sf::Texture* texture;
    bool hasObject;

public:
    //Cell(sf::Texture& const texture, Cell::Type const& type);
    Cell(sf::Vector2f size);
    virtual ~Cell();

    void setStatus(bool hasObject);
    void setNumber(int number);
    void setPosition(sf::Vector2f position);
    void setPosition(int x, int y);

    bool isEmpty() const;
    int getNumber() const;
    sf::Vector2f getPosition() const;
    sf::Vector2f getSize() const;
    float getOutlineThickness() const;

    bool contains(sf::Vector2f const& point) const;
    bool contains(sf::Vector2i const& point) const;

    //static void play_animation();

    //friend Unit;

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

