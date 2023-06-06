#include "Game.h"
#include "Manager.h"


Game::Game() : window(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), WINDOW_NAME) {
    this->window.setFramerateLimit(WINDOW_FRAMERATE);
    //this->window.setKeyRepeatEnabled(false);
    Manager::get_instance();
}

void Game::process() {
    Manager::get_instance().update(this->window, this->event);
    while (this->window.isOpen()) {
        this->update();
        this->draw();

        /*Unit* tmp = Unit::celected_unit;
        if (tmp) {
            std::cout << '\n';
            for (auto cell : tmp->attack_zone.get_zone()) {
                if (!cell) continue;
                std::cout << cell->get_number() << (cell->get_unit() ? "U" : "E") << ' ';
            }
            system("cls");
        }*/
   }
}

void Game::update() {
    while (this->window.pollEvent(this->event)) {
        switch (this->event.type) {
        case::sf::Event::Closed:
            window.close();
            break;

        default:
            break;
        }
    }
        Manager::get_instance().update(this->window, this->event);
}

void Game::draw() {
    window.clear(sf::Color::White);

    window.draw(map::Map::get_instance());
    Manager::get_instance().draw_units(window);

    window.display();
}
