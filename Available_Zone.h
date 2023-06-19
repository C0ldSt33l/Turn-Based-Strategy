#pragma once

#include <vector>

#include "Cell.h"


class Available_Zone {
public:
    enum class Action_Type {
        MOVE,
        ATTACK,
    };

    enum class Type{
        RECT,
        LINE,
    };

    const static std::vector<sf::Int32> RECT_FORM;
    const static std::vector<sf::Int32> LINE_FORM;

    const static Available_Zone RECT_ZONE;
    const static Available_Zone LINE_ZONE;

private:
    Available_Zone::Type type;
    Available_Zone::Action_Type action_type;
    std::vector<sf::Int32> form;

    std::vector<Cell*> cells;
    Cell* bound_point;

public:
    Available_Zone(const Available_Zone::Action_Type action_type, Available_Zone const& zone);

    void set_form(std::vector<sf::Int32> const& form);
    std::vector<Cell*>& get_zone();
    
    bool contain(Cell const* cell) const;
    void update(Cell* position);
    Available_Zone get_invert_zone() const;

private:
    Available_Zone(const Available_Zone::Type type);

    void check_rect_form(std::vector<sf::Int32>& indexes);
    void check_line_form(std::vector<sf::Int32>& indexes);

    void update_cells(std::vector<sf::Int32> const& idxs);

    static std::vector<sf::Int32> invert_form(Available_Zone::Type type);

};
