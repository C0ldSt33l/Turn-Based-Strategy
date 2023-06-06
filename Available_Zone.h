#pragma once

#include <vector>

#include "Cell.h"


class Available_Zone {
public:
    enum class Type{
        RECT,
        LINE,
    };

private:
    Available_Zone::Type type;
    std::vector<sf::Int32> form;

    std::vector<Cell*> cells;
    Cell* bound_point;

public:
    const static std::vector<sf::Int32> RECT;
    const static std::vector<sf::Int32> LINE;

public:
    Available_Zone();
    Available_Zone(Cell* const position, Available_Zone::Type type);

    std::vector<Cell*>& get_zone();
    bool contain(Cell const* cell) const;
    void update(Cell* position);
    void invert();

private:
    void check_rect_form(std::vector<sf::Int32>& indexes);
    void check_line_form(std::vector<sf::Int32>& indexes);
};

