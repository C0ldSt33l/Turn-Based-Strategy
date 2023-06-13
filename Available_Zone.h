#pragma once

#include <vector>

#include "Cell.h"


class Available_Zone {
public:
    enum class Type{
        RECT,
        LINE,
    };

    const static std::vector<sf::Int32> RECT_FORM;
    const static std::vector<sf::Int32> LINE_FORM;

private:
    Available_Zone::Type type;
    std::vector<sf::Int32> form;

    std::vector<Cell*> cells;
    Cell* bound_point;

public:
    Available_Zone(Cell* const position, Available_Zone::Type type);

    void set_form(std::vector<sf::Int32> const& form);
    std::vector<Cell*>& get_zone();
    bool contain(Cell const* cell) const;
    void update(Cell* position);

    static std::vector<sf::Int32> invert_form(Available_Zone::Type type);

private:
    void check_rect_form(std::vector<sf::Int32>& indexes);
    void check_line_form(std::vector<sf::Int32>& indexes);
};

