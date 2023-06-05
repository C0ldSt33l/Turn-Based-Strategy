#include <unordered_set>

#include "Available_Zone.h"
#include "Map.h"


// MEMBERS
const std::vector<sf::Int32> Available_Zone::RECT = {
    -map::MAP_SIZE.x - 1, -map::MAP_SIZE.x, -map::MAP_SIZE.x + 1,
             -1         ,         0       ,           1         ,
     map::MAP_SIZE.x - 1,  map::MAP_SIZE.x,  map::MAP_SIZE.x + 1,
};
const std::vector<sf::Int32> Available_Zone::LINE = {
    1, 2, 3, 4, 5, 6, 7, 8
};


// METHODS
Available_Zone::Available_Zone() {}
Available_Zone::Available_Zone(Cell* const position, Available_Zone::Type type) : type(type) {
    switch (type) {
    case Available_Zone::Type::RECT:
        this->form = Available_Zone::RECT;
        break;

    case Available_Zone::Type::LINE:
        this->form = Available_Zone::LINE;
        break;
    }

    this->cells.resize(this->form.size());
    this->update(position);
}

std::vector<Cell*>& Available_Zone::get_zone() {
    return this->cells;
}

void Available_Zone::update(Cell const* position) {
    std::vector<sf::Int32> idxs; idxs.resize(this->form.size());

    for (int i = 0; i < this->cells.size(); ++i) {
        idxs[i] = position->get_number() + this->form[i];
    }

    switch (this->type) {
    case Available_Zone::Type::RECT:
        this->check_rect_form(idxs);
        break;

    case Available_Zone::Type::LINE:
        break;
    }

    for (int i = 0; i < this->cells.size(); ++i) {
        this->cells[i] = idxs[i] >= 0 && idxs[i] < map::CELL_COUNT  && map::Map::get_instance()[idxs[i]].is_empty() ?
            &map::Map::get_instance()[idxs[i]] :
            nullptr;
    }
}

void Available_Zone::invert() {
    switch (this->type) {
    case Available_Zone::Type::RECT:
        break;

    case Available_Zone::Type::LINE:
        for (auto offset : this->form) {
            offset *= -1;
        }
        break;
    }
}

void Available_Zone::check_rect_form(std::vector<sf::Int32>& indexes) {
    for (int i = 0; i < 3; ++i) {
        sf::Int16 row_index = i * 3;
        if ((indexes[row_index] / map::MAP_SIZE.x + indexes[row_index + 1] / map::MAP_SIZE.x) % 2) {
            indexes[row_index] = -1;
        }
        else if ((indexes[row_index] / map::MAP_SIZE.x + indexes[row_index + 2] / map::MAP_SIZE.x) % 2) {
            indexes[row_index + 2] = -1;
        }

        sf::Int32 col_index = i;
        if ((indexes[col_index] % map::MAP_SIZE.x + indexes[col_index + 3] % map::MAP_SIZE.x) % 2) {
            indexes[col_index] -1;
        }
        else if ((indexes[col_index] % map::MAP_SIZE.x + indexes[col_index + 6] % map::MAP_SIZE.x) % 2) {
            indexes[col_index + 6] = -1;
        }
    }
}
