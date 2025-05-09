#include "visualLair.h"
#include "textureManager.h"

std::unordered_map<std::type_index, std::function<std::shared_ptr<VisualEnemy>(const std::shared_ptr<Enemy>& enemy)>> VisualLair::releaseVisualEnemyTable_ = {
    {std::type_index(typeid(Aviation)), [](const std::shared_ptr<Enemy>& enemy) {
        sf::Texture& texture = TextureManager::getTexture("gui/sprites/enemiesSprites/aviation.png");
        return std::make_shared<VisualEnemy>(texture, enemy); }},
    {std::type_index(typeid(LightInfantry)), [](const std::shared_ptr<Enemy>& enemy) {
        sf::Texture& texture = TextureManager::getTexture("gui/sprites/enemiesSprites/lightInfantry.png");
        return std::make_shared<VisualEnemy>(texture, enemy); }},
    {std::type_index(typeid(HeavyInfantry)), [](const std::shared_ptr<Enemy>& enemy) {
        sf::Texture& texture = TextureManager::getTexture("gui/sprites/enemiesSprites/heavyInfantry.png");
        return std::make_shared<VisualEnemy>(texture, enemy); }},
    {std::type_index(typeid(Hero<Aviation, AviationStats>)), [](const std::shared_ptr<Enemy>& enemy) {
        sf::Texture& texture = TextureManager::getTexture("gui/sprites/enemiesSprites/aviation.png");
        return std::make_shared<VisualEnemy>(texture, enemy); }},
    {std::type_index(typeid(Hero<LightInfantry, LightInfantryStats>)), [](const std::shared_ptr<Enemy>& enemy) {
        sf::Texture& texture = TextureManager::getTexture("gui/sprites/enemiesSprites/lightInfantry.png");
        return std::make_shared<VisualEnemy>(texture, enemy); }},
    {std::type_index(typeid(Hero<HeavyInfantry, HeavyInfantryStats>)), [](const std::shared_ptr<Enemy>& enemy) {
        sf::Texture& texture = TextureManager::getTexture("gui/sprites/enemiesSprites/heavyInfantry.png");
        return std::make_shared<VisualEnemy>(texture, enemy); }}
};


std::shared_ptr<VisualEnemy> VisualLair::releaseVisualEnemy(const std::shared_ptr<Enemy>& enemy) {
    auto it = releaseVisualEnemyTable_.find(typeid(*enemy));
    if (it != releaseVisualEnemyTable_.end()) {
        return it->second(enemy);
    }
    throw std::invalid_argument("Visual enemy not found.");
}