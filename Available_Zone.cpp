#include <unordered_set>

#include "Available_Zone.h"
#include "Map.h"


// MEMBERS
const std::vector<sf::Int32> Available_Zone::RECT_FORM = {
    -map::MAP_SIZE.x - 1, -map::MAP_SIZE.x, -map::MAP_SIZE.x + 1,
             -1                           ,           1         ,
     map::MAP_SIZE.x - 1,  map::MAP_SIZE.x,  map::MAP_SIZE.x + 1,
};
const std::vector<sf::Int32> Available_Zone::LINE_FORM = {
    1, 2, 3, 4, 5, 6, 7, 8
};

const Available_Zone Available_Zone::RECT_ZONE(Available_Zone::Type::RECT);
const Available_Zone Available_Zone::LINE_ZONE(Available_Zone::Type::LINE);

// METHODS
Available_Zone::Available_Zone(const Available_Zone::Type type) : type(type), bound_point(nullptr) {
    switch (this->type) {
    case Available_Zone::Type::RECT:
        this->form = Available_Zone::RECT_FORM;
        break;

    case Available_Zone::Type::LINE:
        this->form = Available_Zone::LINE_FORM;
        break;
    }

    this->cells.resize(this->form.size());
}
Available_Zone::Available_Zone(const Available_Zone::Action_Type action_type, Available_Zone const& zone) :
    type(zone.type), form(zone.form), bound_point(zone.bound_point), cells(zone.cells), action_type(action_type) {}

void Available_Zone::set_form(std::vector<sf::Int32> const& form) {
    this->form = form;
    this->update(this->bound_point);
}

std::vector<Cell*>& Available_Zone::get_zone() {
    return this->cells;
}
bool Available_Zone::contain(Cell const* cell) const {
    for (auto c : this->cells) {
        if (cell == c)
            return true;
    }

    return false;
}
void Available_Zone::update(Cell* position) {
    this->bound_point = position;
    std::vector<sf::Int32> idxs(this->form.size());
    for (int i = 0; i < this->cells.size(); ++i) {
        idxs[i] = position->get_number() + this->form[i];
    }

    switch (this->type) {
    case Available_Zone::Type::RECT:
        this->check_rect_form(idxs);
        break;

    case Available_Zone::Type::LINE:
        this->check_line_form(idxs);
        break;
    }

    this->update_cells(idxs);
}

Available_Zone Available_Zone::get_invert_zone() const {
    Available_Zone zone = *this;

    switch (this->type) {
    case Available_Zone::Type::RECT:
        zone.form = Available_Zone::invert_form(Available_Zone::Type::RECT);
        break;
    case Available_Zone::Type::LINE:
        zone.form = Available_Zone::invert_form(Available_Zone::Type::LINE);
        break;
    }

    return zone;
}

// STATIC METHODS
void Available_Zone::check_rect_form(std::vector<sf::Int32>& indexes) {
    sf::Int32 row = this->bound_point->get_row_number(),
              col = this->bound_point->get_col_number();
    for (int i = 0; i < indexes.size(); ++i) {
        sf::Int32 diff_row = abs(row - indexes[i] / map::MAP_SIZE.x),
                  diff_col = abs(col - indexes[i] % map::MAP_SIZE.x);
       
        if (diff_row != 0 && diff_row != 1 || diff_col != 0 && diff_col != 1) {
            indexes[i] = -1;
        }
    }
}
void Available_Zone::check_line_form(std::vector<sf::Int32>& indexes) {
    sf::Int32 row = this->bound_point->get_row_number();
    for (int i = 0; i < this->form.size() ; ++i) {
        if (row != indexes[i] / map::MAP_SIZE.x) {
            for (; i < this->form.size(); ++i) {
                indexes[i] = -1;
            }
            break;
        }
    }
}

void Available_Zone::update_cells(std::vector<sf::Int32> const& idxs) {
    if (Available_Zone::Action_Type::MOVE == this->action_type) {
        for (int i = 0; i < idxs.size(); ++i) {
            this->cells[i] = idxs[i] >= 0 && idxs[i] < map::CELL_COUNT && map::Map::get_instance()[idxs[i]].is_empty() ?
                &map::Map::get_instance()[idxs[i]] :
                nullptr;
        }
    }
    else {
        for (int i = 0; i < idxs.size(); ++i) {
            this->cells[i] = idxs[i] >= 0 && idxs[i] < map::CELL_COUNT ?
                &map::Map::get_instance()[idxs[i]] :
                nullptr;
        }
    }
}

std::vector<sf::Int32> Available_Zone::invert_form(Available_Zone::Type type) {
    std::vector<sf::Int32> form;
    
    switch (type) {
    case Available_Zone::Type::RECT:
        form = Available_Zone::RECT_FORM;
        break;

    case Available_Zone::Type::LINE:
        form = Available_Zone::LINE_FORM;
        for (int i = 0; i < form.size(); ++i) {
            form[i] *= -1;
        }
        break;
    }

    return form;
}
