#include "Game.h"


ResourceManager* ResourceManager::instance = ResourceManager::getInstance();

Game::Game() {
    this->window.create(sf::VideoMode(800, 600), "Turn-based strategy");
    this->window.setFramerateLimit(60);

    //this->res_manager = ResourceManager::getInstance();
}

Game::~Game() {
}

void Game::process() {
}

void Game::menu() {
}

void Game::draw() {
}
