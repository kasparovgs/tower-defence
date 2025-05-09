#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H


#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <memory>
#include <stdexcept>

class TextureManager {
public:
    TextureManager() = delete;
    static sf::Texture& getTexture(const std::string& filename);
};



#endif