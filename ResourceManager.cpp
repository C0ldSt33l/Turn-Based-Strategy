#include <iostream>

#include "ResourceManager.h"


ResourceManager::ResourceManager() {
    this->textures;
}

ResourceManager& ResourceManager::getInstance() {
    static ResourceManager instance;
    return instance;
}

void ResourceManager::add_texture(std::string const& file) {

    if (this->textures.find(file) != textures.cend()) {
        this->textures[file] = ResourceManager::load_texture(file);
    }
}

sf::Texture* ResourceManager::load_texture(std::string const& file) {
    sf::Texture* texture = new sf::Texture;

    if (!texture->loadFromFile(file)) {
        std::cout << "Error with loading of texture: " << file << '\n';
        exit(1);
    }
    
    return texture;
}

