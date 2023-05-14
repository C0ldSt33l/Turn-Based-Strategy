#pragma once

#include <map>
#include <string>

#include <SFML/Graphics.hpp>


class ResourceManager {
    static ResourceManager* instance;
    std::map<std::string, sf::Texture*> textures;

    ResourceManager() = default;
    ~ResourceManager() = default;
 
public:
    ResourceManager(ResourceManager const& obj) = delete;
    ResourceManager& operator=(ResourceManager const& obj) = delete;

    static ResourceManager* getInstance();

    void add_texture(std::string const& file);

private:
    sf::Texture* load_texture(std::string const& file);
};

//ResourceManager* ResourceManager::instance = nullptr;