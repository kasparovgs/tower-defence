#include "textureManager.h"

sf::Texture& TextureManager::getTexture(const std::string& filename) {
    static std::unordered_map<std::string, std::shared_ptr<sf::Texture>> textures;
    if (textures.find(filename) != textures.end()) {
        return *textures[filename];
    }

    auto texture = std::make_shared<sf::Texture>();
    if (!texture->loadFromFile(filename)) {
        throw std::runtime_error("Failed to load texture: " + filename);
    }

    textures[filename] = texture;
    return *textures[filename];
}