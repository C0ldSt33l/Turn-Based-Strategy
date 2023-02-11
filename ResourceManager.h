#pragma once
class ResourceManager {
private:
    static ResourceManager* instance;

    ResourceManager();
public:
    ResourceManager(ResourceManager& const obj) = delete;
    ResourceManager& operator=(ResourceManager& const obj) = delete;
    ~ResourceManager();

    //static ResourceManager* getInstance();
};

//ResourceManager* resourceManager = ResourceManager::getInstance();
