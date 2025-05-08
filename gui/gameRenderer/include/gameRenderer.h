#ifndef GAMERENDERER_H
#define GAMERENDERER_H

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <memory>
#include <vector>
#include "visualLair.h"

class Game;
class VisualEnemy;
#include "visualStructure.h"

class GameRenderer {
private:
    sf::RenderWindow& window_;
    Game& game_;
    sf::Font font_;
    std::vector<std::shared_ptr<VisualEnemy>> visualEnemies_;
    std::vector<std::shared_ptr<VisualStructure>> visualStructures_;
    sf::Sprite mapSprite_;
    sf::Text timeText_;

    std::unordered_map<std::string, std::shared_ptr<sf::Drawable>> elements_;
    static std::unordered_map<std::type_index,
                              std::function<std::vector<std::shared_ptr<sf::Drawable>>(const std::shared_ptr<EnemyStats>& enemyStats,
                                                                                       const sf::Font& font,
                                                                                       std::size_t level,
                                                                                       std::size_t currentHP)>> createVisualEnemyStatsTable_;
    
    static std::unordered_map<std::type_index,
                              std::function<std::vector<std::shared_ptr<sf::Drawable>>(const std::shared_ptr<StructureStats>& structureStats,
                                                                                       const sf::Font& font,
                                                                                       std::size_t level)>> createVisualStructureStatsTable_;
public:
    GameRenderer(sf::RenderWindow& window,
                 Game& game);

    void render();
    void renderEnemyStats(std::shared_ptr<VisualEnemy> visualEnemy);
    void renderStructureStats(std::shared_ptr<VisualStructure> visualStructure);
    void renderNoMoneyAlert();
    void renderStructureAlreadyMaxed();
    void renderStructureUpgradeSuccess();
    void renderGameOverLost();
    void update();
    bool handleMouseClickMakeMove(const sf::Vector2i& mousePos);
    bool handleMouseClickCollectGold(const sf::Vector2i& mousePos);
    bool handleMouseClickLevelUp(const sf::Vector2i& mousePos);
    std::shared_ptr<VisualEnemy> handleMouseClickEnemy(const sf::Vector2i& mousePos);
    std::shared_ptr<VisualStructure> handleMouseClickStructure(const sf::Vector2i& mousePos);
    static std::shared_ptr<sf::Text> createText(const sf::Font& font,
                                     std::size_t charSize,
                                     sf::Color color,
                                     std::size_t posX,
                                     std::size_t posY);
};


#endif