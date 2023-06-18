#include "Game.h"
#include "Manager.h"


Game::Game() : window(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), WINDOW_NAME), interface("fonts//RED.ttf") {
    this->window.setFramerateLimit(WINDOW_FRAMERATE);
    //sthis->window.setKeyRepeatEnabled(false);
    Manager::get_instance();
}

void Game::process() {
    Manager::get_instance().update(this->window, this->event);
    while (this->window.isOpen()) {
        this->update();
        this->draw();
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
    this->interface.update();
}

void Game::draw() {
    for (auto unit : Manager::get_instance().get_units()) {
        std::cout << "Unit<" << unit->get_id() << ">:\n";
        std::cout << "Hp: " << unit->get_hp() << "of" << unit->get_max_hp() << '\n';
        std::cout << "Action point: " << unit->get_action_point() << '\n';
        std::cout << "Move point: " << unit->get_move_point() << '\n';
    }
    //std::cout << "\n\nPlayer team size: " << Manager::get_instance().teams[0].size() << '\n';
    //std::cout << "Enemy team size: " << Manager::get_instance().teams[1].size() << '\n';
    system("cls");
   
    //map::Map::get_instance().draw_unit_position();
    window.clear(sf::Color::White);

    window.draw(map::Map::get_instance());
    Manager::get_instance().draw_units(window);
    window.draw(this->interface);

    window.display();
}
