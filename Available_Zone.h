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

public:
    const static std::vector<sf::Int32> RECT;
    const static std::vector<sf::Int32> LINE;

public:
    Available_Zone();
    Available_Zone(Cell* const position, Available_Zone::Type type);

    std::vector<Cell*>& get_zone();
    void update(Cell const* position);
    void invert();

private:
    void check_rect_form(std::vector<sf::Int32>& indexes);
};

