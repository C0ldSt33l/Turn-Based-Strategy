#include "Available_Zone.h"
#include "Map.h"


// MEMBERS
const std::vector<sf::Int32> Available_Zone::AROUND = {
    -map::MAP_SIZE.x - 1, -map::MAP_SIZE.x, -map::MAP_SIZE.x + 1,
             -1         ,                            +1         ,
    map::MAP_SIZE.x - 1 , map::MAP_SIZE.x , map::MAP_SIZE.x + 1 ,
};
const std::vector<sf::Int32> Available_Zone::LINE = {
    1, 2, 3, 4, 5, 6, 7, 8
};

Available_Zone::Available_Zone() {
}

// METHODS
Available_Zone::Available_Zone(Cell* const position, Available_Zone::Type type) : type(type) {
    switch (type) {
    case Available_Zone::Type::AROUND:
        this->form = Available_Zone::AROUND;
        break;

    case Available_Zone::Type::LINE:
        this->form = Available_Zone::LINE;
        break;

    default:
        break;
    }

    this->cells.resize(this->form.size());
    this->update(position);
}

void Available_Zone::update(Cell const* position) {
    for (int i = 0; i < this->cells.size(); ++i) {
        this->cells[i] = &map::Map::get_instance()[position->get_number() + this->form[i]];
    }
}

std::vector<sf::Uint16> Available_Zone::invert() {
    switch (this->type) {
    case Available_Zone::Type::AROUND:
        break;

    case Available_Zone::Type::LINE:
        break;

    default:
        break;
    }

    return std::vector<sf::Uint16>();
}
