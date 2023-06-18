#include "Interface.h"

#include <format>

#include "Interface.h"
#include "Unit.h"
#include "Game.h"


// Interface
Interface::Interface(std::string const& file) : sf::Drawable(), unit_ui(this->font) {
    if (!this->font.loadFromFile(file)) {
        exit(1);
    }

    this->turn.setFont(this->font);
    this->turn.setCharacterSize(48);
    this->turn.setPosition(WINDOW_SIZE.x / 2 - 100, 0);

    this->turn.setFillColor(sf::Color::Blue);
    this->turn.setString(Interface::PLAYER_TURN);
}
Interface::~Interface() {}

void Interface::update() {
    this->unit_ui.update();
}

void Interface::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(this->turn);
    target.draw(this->unit_ui);

    if (!Unit::celected_unit) return;
}

void Interface::set_text(sf::Text& text, std::string const& string, sf::Color const& color) {
    text.setString(string);
    text.setFillColor(color);
}

// Unit_Interface
Interface::Unit_Interface::Unit_Interface(sf::Font const& font) : sf::Drawable(), rect({ 130, 80 }), selected_unit(nullptr) {
    this->rect.setPosition({ 0, 0 });
    this->rect.setFillColor(sf::Color::Yellow);
    //Interface::set_text(this->text, "dhfkd", sf::Color::Black);
    this->text.setFont(font);
    this->text.setCharacterSize(20);
    this->text.setPosition(this->rect.getPosition().x + 20, this->rect.getPosition().y);
    Interface::set_text(this->text, "HP: 100/100", sf::Color::Black);
}

void Interface::Unit_Interface::update() {
    if (!Unit::celected_unit) return;
    this->text.setString(
        std::format(UNIT_STRING,
            Unit::celected_unit->get_hp(), Unit::celected_unit->get_max_hp(),
            Unit::celected_unit->get_action_point(), Unit::celected_unit->get_move_point())
    );
}

void Interface::Unit_Interface::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (!Unit::celected_unit) return;

    target.draw(this->rect);
    target.draw(this->text);
}