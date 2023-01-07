#include<SFML/Graphics/RenderWindow.hpp>

#include "Cell.h"

bool Cell::isEmpty(){
    return hasObject;
}

void Cell::draw(sf::RenderWindow& window) {
    //window.draw(cell);
}
