#pragma once

#include <vector>

#include "Cell.h"


class Available_Zone {
public:
    enum class Type{
        AROUND,
        LINE,
    };

private:
    Available_Zone::Type type;
    std::vector<sf::Int32> form;

    std::vector<Cell*> cells;

public:
    const static std::vector<sf::Int32> AROUND;
    const static std::vector<sf::Int32> LINE;

public:
    Available_Zone();
    Available_Zone(Cell* const position, Available_Zone::Type type);

    void update(Cell const* position);
    std::vector<sf::Uint16> invert();
};

