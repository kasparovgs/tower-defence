#include "visualStructureFactory.h"
#include "textureManager.h"

std::unordered_map<int, std::string> wallTextures = {
    {1, "gui/sprites/wallSprites/wall1.png"},
    {2, "gui/sprites/wallSprites/wall2.png"},
    {3, "gui/sprites/wallSprites/wall3.png"},
    {4, "gui/sprites/wallSprites/wall4.png"}
};


std::unordered_map<int, std::string> castleTextures = {
    {1, "gui/sprites/castleSprites/castle1.png"},
    {2, "gui/sprites/castleSprites/castle2.png"},
    {3, "gui/sprites/castleSprites/castle3.png"},
    {4, "gui/sprites/castleSprites/castle4.png"}
};


std::unordered_map<int, std::string> towerTextures = {
    {1, "gui/sprites/towerSprites/tower1.png"},
    {2, "gui/sprites/towerSprites/tower2.png"},
    {3, "gui/sprites/towerSprites/tower3.png"},
    {4, "gui/sprites/towerSprites/tower4.png"}
};


std::unordered_map<int, std::string> lairTextures = {
    {1, "gui/sprites/lairSprites/lair1.png"},
    {2, "gui/sprites/lairSprites/lair2.png"},
    {3, "gui/sprites/lairSprites/lair3.png"},
    {4, "gui/sprites/lairSprites/lair4.png"}
};


std::unordered_map<std::type_index, std::function<std::shared_ptr<VisualStructure>(const std::shared_ptr<Structure>& structure)>> VisualStructureFactory::releaseVisualStructureTable_ = {
    {std::type_index(typeid(Wall)), [](const std::shared_ptr<Structure>& structure) {
        int level = structure->getLevel();
        std::string texturePath = wallTextures.at(level);
        sf::Texture& texture = TextureManager::getTexture(texturePath);
        return std::make_shared<VisualStructure>(texture, structure); }},
    {std::type_index(typeid(Castle)), [](const std::shared_ptr<Structure>& structure) {
        int level = structure->getLevel();
        std::string texturePath = castleTextures.at(level);
        sf::Texture& texture = TextureManager::getTexture(texturePath);
        return std::make_shared<VisualStructure>(texture, structure); }},
    {std::type_index(typeid(Tower)), [](const std::shared_ptr<Structure>& structure) {
        int level = structure->getLevel();
        std::string texturePath = towerTextures.at(level);
        sf::Texture& texture = TextureManager::getTexture(texturePath);
        return std::make_shared<VisualStructure>(texture, structure); }},
    {std::type_index(typeid(Lair)), [](const std::shared_ptr<Structure>& structure) {
        int level = structure->getLevel();
        std::string texturePath = lairTextures.at(level);
        sf::Texture& texture = TextureManager::getTexture(texturePath);
        return std::make_shared<VisualStructure>(texture, structure); }}
};


std::shared_ptr<VisualStructure> VisualStructureFactory::releaseVisualStructure(const std::shared_ptr<Structure>& structure) {
    auto it = releaseVisualStructureTable_.find(typeid(*structure));
    if (it != releaseVisualStructureTable_.end()) {
        return it->second(structure);
    }
    throw std::invalid_argument("Visual structure not fount");
}