#pragma once

#include <SFML/Graphics.hpp>


class Unit;
class Cell : public sf::Drawable {
    enum class Type {
        EATHE,
        WATER,
        WALL,
    };

    sf::Uint16 number;
    sf::RectangleShape rect;
    //static sf::Texture* texture;
    bool has_object;
    Unit* unit;

public:
    //Cell(sf::Texture& const texture, Cell::Type const& type);
    Cell(sf::Vector2f size);
    virtual ~Cell();

    void set_status(bool hasObject);
    void set_number(int number);
    void set_position(sf::Vector2f const& position);
    void set_position(int x, int y);
    void set_color(sf::Color const& color);
    void make_empty();

    bool is_empty() const;
    int get_number() const;
    Unit* get_unit() const;
    sf::Int16 get_row_number() const;
    sf::Int16 get_col_number() const;
    sf::Vector2f get_position() const;
    sf::Vector2f get_size() const;
    float get_outline_thickness() const;
    bool in_available_zone(std::vector<Cell*> const& zone) const;

    bool contains(sf::Vector2f const& point) const;
    bool contains(sf::Vector2i const& point) const;

    //static void play_animation();
    friend class Unit;

private:
    static sf::Uint16 generate_num();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

