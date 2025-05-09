#include "gameRenderer.h"
#include "game.h"
#include "enemy.h"
#include "visualLair.h"
#include "visualStructureFactory.h"
#include "textureManager.h"
#include "castle.h"


GameRenderer::GameRenderer(sf::RenderWindow& window,
                           Game& game) :  window_(window),
                                          game_(game) {
    sf::Texture& mapTexture = TextureManager::getTexture("gui/sprites/pictures/map.png");
    mapSprite_.setTexture(mapTexture);

    if (!font_.loadFromFile("gui/fonts/KZSupercell-Magic.ttf")) {
        throw std::invalid_argument("The font is incorrect");
    }


    sf::Text goldText;
    goldText.setFont(font_);
    goldText.setString(L"Текущее золото: " + std::to_wstring(GlobalGold::getGold()));
    goldText.setCharacterSize(24);
    goldText.setFillColor(sf::Color::White);
    goldText.setPosition(1500, 50);
    auto goldTextPtr = std::make_shared<sf::Text>(goldText);
    elements_["GoldText"] = goldTextPtr;

    sf::Text timeText;
    timeText.setFont(font_);
    timeText.setString(L"Время: " + std::to_wstring(GlobalTime::getTime()));
    timeText.setCharacterSize(24);
    timeText.setFillColor(sf::Color::White);
    timeText.setPosition(1500, 100);
    auto timeTextPtr = std::make_shared<sf::Text>(timeText);
    elements_["TimeText"] = timeTextPtr;


    sf::Texture& buttonMakeMoveTexture = TextureManager::getTexture("gui/sprites/buttons/makeMoveButton.png");
    sf::Sprite buttonMakeMoveSprite;
    buttonMakeMoveSprite.setTexture(buttonMakeMoveTexture);
    buttonMakeMoveSprite.setScale(0.8f, 0.8f);
    buttonMakeMoveSprite.setPosition(1500, 900);
    auto buttonMakeMoveSpritePtr = std::make_shared<sf::Sprite>(buttonMakeMoveSprite);
    elements_["MakeMoveButton"] = buttonMakeMoveSpritePtr;

    sf::Texture& buttonCollectGoldTexture = TextureManager::getTexture("gui/sprites/buttons/collectGoldButton.png");
    sf::Sprite buttonCollectGoldSprite;
    buttonCollectGoldSprite.setTexture(buttonCollectGoldTexture);
    buttonCollectGoldSprite.setScale(0.6f, 0.6f);
    buttonCollectGoldSprite.setPosition(1500, 300);
    auto buttonCollectGoldSpritePtr = std::make_shared<sf::Sprite>(buttonCollectGoldSprite);
    elements_["CollectGoldButton"] = buttonCollectGoldSpritePtr;

    sf::Text collectGoldText;
    collectGoldText.setFont(font_);
    auto castleStructure = game_.getCastle();
    auto castle = std::static_pointer_cast<Castle>(castleStructure);
    collectGoldText.setString(std::to_wstring(castle->getAccumulatedGold()));
    collectGoldText.setCharacterSize(24);
    collectGoldText.setFillColor(sf::Color::White);
    collectGoldText.setPosition(1620, 375);
    auto collectGoldTextPtr = std::make_shared<sf::Text>(collectGoldText);
    elements_["CollectGoldText"] = collectGoldTextPtr;

    sf::Texture& buttonLevelUpTexture = TextureManager::getTexture("gui/sprites/buttons/levelUpButton.png");
    sf::Sprite buttonLevelUpSprite;
    buttonLevelUpSprite.setTexture(buttonLevelUpTexture);
    buttonLevelUpSprite.setScale(0.8f, 0.8f);
    buttonLevelUpSprite.setPosition(0, 900);
    auto buttonLevelUpSpritePtr = std::make_shared<sf::Sprite>(buttonLevelUpSprite);
    elements_["LevelUpButton"] = buttonLevelUpSpritePtr;

    sf::Texture& NoMoneyTexture = TextureManager::getTexture("gui/sprites/pictures/noMoneyAlert.png");
    sf::Sprite NoMoneySprite;
    NoMoneySprite.setTexture(NoMoneyTexture);
    NoMoneySprite.setScale(0.8f, 0.8f);
    NoMoneySprite.setPosition(0, 700);
    auto NoMoneySpritePtr = std::make_shared<sf::Sprite>(NoMoneySprite);
    elements_["NoMoneyAlert"] = NoMoneySpritePtr;

    sf::Texture& StructureAlreadyMaxedTexture = TextureManager::getTexture("gui/sprites/pictures/structureAlreadyMaxed.png");
    sf::Sprite StructureAlreadyMaxedSprite;
    StructureAlreadyMaxedSprite.setTexture(StructureAlreadyMaxedTexture);
    StructureAlreadyMaxedSprite.setScale(0.8f, 0.8f);
    StructureAlreadyMaxedSprite.setPosition(0, 700);
    auto StructureAlreadyMaxedSpritePtr = std::make_shared<sf::Sprite>(StructureAlreadyMaxedSprite);
    elements_["StructureAlreadyMaxed"] = StructureAlreadyMaxedSpritePtr;

    sf::Texture& StructureUpgradeSuccessTexture = TextureManager::getTexture("gui/sprites/pictures/structureUpgradeSuccess.png");
    sf::Sprite StructureUpgradeSuccessSprite;
    StructureUpgradeSuccessSprite.setTexture(StructureUpgradeSuccessTexture);
    StructureUpgradeSuccessSprite.setScale(0.8f, 0.8f);
    StructureUpgradeSuccessSprite.setPosition(0, 700);
    auto StructureUpgradeSuccessSpritePtr = std::make_shared<sf::Sprite>(StructureUpgradeSuccessSprite);
    elements_["StructureUpgradeSucces"] = StructureUpgradeSuccessSpritePtr;

    sf::Texture& GameOverLostTexture = TextureManager::getTexture("gui/sprites/pictures/gameOverLost.png");
    sf::Sprite GameOverLostSprite;
    GameOverLostSprite.setTexture(GameOverLostTexture);
    GameOverLostSprite.setScale(0.8f, 0.8f);
    GameOverLostSprite.setPosition(960, 540);
    auto GameOverLostSpritePtr = std::make_shared<sf::Sprite>(GameOverLostSprite);
    elements_["GameOverLost"] = GameOverLostSpritePtr;

    auto enemies = game_.getEnemies();
    for (std::size_t i = 0; i < enemies.size(); i++) {
        auto enemy = enemies[i];
        auto visualEnemy = VisualLair::releaseVisualEnemy(enemy);
        visualEnemies_.push_back(visualEnemy);
    }

    auto structures = game_.getStructures();
    for (std::size_t i = 0; i < structures.size(); i++) {
        auto structure = structures[i];
        auto visualStructure = VisualStructureFactory::releaseVisualStructure(structure);
        visualStructures_.push_back(visualStructure);
    }
}


void GameRenderer::renderGameOverLost() {
    window_.draw(*elements_["GameOverLost"]);
    window_.display();
}


void GameRenderer::render() {
    update();
    window_.clear();
    window_.draw(mapSprite_);
    window_.draw(*elements_["TimeText"]);
    window_.draw(*elements_["GoldText"]);
    window_.draw(*elements_["MakeMoveButton"]);
    window_.draw(*elements_["CollectGoldButton"]);
    window_.draw(*elements_["CollectGoldText"]);

    for (const auto& visualStructure : visualStructures_) {
        window_.draw(*visualStructure);
    }
    
    for (const auto& visualEnemy : visualEnemies_) {
        window_.draw(*visualEnemy);
    }
    window_.display();

}


void GameRenderer::update() {
    auto time = std::static_pointer_cast<sf::Text>(elements_["TimeText"]);
    time->setString(L"Время: " + std::to_wstring(GlobalTime::getTime()));

    auto gold = std::static_pointer_cast<sf::Text>(elements_["GoldText"]);
    gold->setString(L"Текущее золото: " + std::to_wstring(GlobalGold::getGold()));

    auto accumulatedGold = std::static_pointer_cast<sf::Text>(elements_["CollectGoldText"]);
    auto castleStructure = game_.getCastle();
    auto castle = std::static_pointer_cast<Castle>(castleStructure);
    accumulatedGold->setString(std::to_wstring(castle->getAccumulatedGold()));

    auto structures = game_.getStructures();
    visualStructures_.clear();
    for (const auto& structure : structures) {
        if (!structure->getValidity()) {
            continue;
        }
        auto visualStructure = VisualStructureFactory::releaseVisualStructure(structure);
        visualStructures_.push_back(visualStructure);
    }


    auto enemies = game_.getEnemies();
    visualEnemies_.clear();
    for (const auto& enemy : enemies) {
        if (enemy->getCurrentHP() == 0) {
            continue;
        }
        auto visualEnemy = VisualLair::releaseVisualEnemy(enemy);
        visualEnemies_.push_back(visualEnemy);
    }
}


void GameRenderer::renderEnemyStats(std::shared_ptr<VisualEnemy> visualEnemy) {
    if (auto enemy = visualEnemy->getLogicEnemy()) {
        std::size_t currentHP = enemy->getCurrentHP();
        std::size_t level = enemy->getLevel();

        auto stats = enemy->getStats();

        std::vector<std::shared_ptr<sf::Drawable>> drawnStats;
        auto it = createVisualEnemyStatsTable_.find(typeid(*stats));
        if (it != createVisualEnemyStatsTable_.end()) {
            drawnStats = it->second(stats, font_, level, currentHP);
        }
        else throw std::invalid_argument("There is no neccessary stats.");
        for (const auto& drawable : drawnStats) {
            window_.draw(*drawable);
        }
        window_.display();
    }
}


void GameRenderer::renderStructureStats(std::shared_ptr<VisualStructure> visualStructure) {
    if (auto structure = visualStructure->getLogicStructure()) {
        std::size_t level = structure->getLevel();

        auto stats = structure->getStats();

        std::vector<std::shared_ptr<sf::Drawable>> drawnStats;
        auto it = createVisualStructureStatsTable_.find(typeid(*stats));
        if (it != createVisualStructureStatsTable_.end()) {
            drawnStats = it->second(stats, font_, level);
        }
        else throw std::invalid_argument("There is no neccessary stats.");
        for (const auto& drawable : drawnStats) {
            window_.draw(*drawable);
        }
        window_.draw(*elements_["LevelUpButton"]);
        window_.display();
    }
}


void GameRenderer::renderNoMoneyAlert() {
    window_.draw(*elements_["NoMoneyAlert"]);
    window_.display();
}


void GameRenderer::renderStructureAlreadyMaxed() {
    window_.draw(*elements_["StructureAlreadyMaxed"]);
    window_.display();
}


void GameRenderer::renderStructureUpgradeSuccess() {
    window_.draw(*elements_["StructureUpgradeSucces"]);
    window_.display();
}


 bool GameRenderer::handleMouseClickMakeMove(const sf::Vector2i& mousePos) {
    sf::Vector2f worldPos = window_.mapPixelToCoords(mousePos);
    auto button = std::static_pointer_cast<sf::Sprite>(elements_["MakeMoveButton"]);
    if (button->getGlobalBounds().contains(static_cast<float>(worldPos.x), static_cast<float>(worldPos.y))) {
        return true;
    }
    return false;
}


bool GameRenderer::handleMouseClickCollectGold(const sf::Vector2i& mousePos) {
    sf::Vector2f worldPos = window_.mapPixelToCoords(mousePos);
    auto button = std::static_pointer_cast<sf::Sprite>(elements_["CollectGoldButton"]);
    if (button->getGlobalBounds().contains(static_cast<float>(worldPos.x), static_cast<float>(worldPos.y))) {
        return true;
    }
    return false;
}


bool GameRenderer::handleMouseClickLevelUp(const sf::Vector2i& mousePos) {
    sf::Vector2f worldPos = window_.mapPixelToCoords(mousePos);
    auto button = std::static_pointer_cast<sf::Sprite>(elements_["LevelUpButton"]);
    if (button->getGlobalBounds().contains(static_cast<float>(worldPos.x), static_cast<float>(worldPos.y))) {
        return true;
    }
    return false;
}


std::shared_ptr<VisualEnemy> GameRenderer::handleMouseClickEnemy(const sf::Vector2i& mousePos) {
    sf::Vector2f worldPos = window_.mapPixelToCoords(mousePos);
    for (const auto& visualEnemy : visualEnemies_) {
        if (visualEnemy->getGlobalBounds().contains(static_cast<float>(worldPos.x), static_cast<float>(worldPos.y))) {
            return visualEnemy;
        }
    }
    return nullptr;
}


std::shared_ptr<VisualStructure> GameRenderer::handleMouseClickStructure(const sf::Vector2i& mousePos) {
    sf::Vector2f worldPos = window_.mapPixelToCoords(mousePos);
    for (const auto& visualStructure : visualStructures_) {
        if (visualStructure->getGlobalBounds().contains(static_cast<float>(worldPos.x), static_cast<float>(worldPos.y))) {
            return visualStructure;
        }
    }
    return nullptr;
}


std::unordered_map<std::type_index,
                   std::function<std::vector<std::shared_ptr<sf::Drawable>>(const std::shared_ptr<EnemyStats>& enemyStats,
                                                                            const sf::Font& font,
                                                                            std::size_t level,
                                                                            std::size_t currentHP)>> GameRenderer::createVisualEnemyStatsTable_ = {
    {std::type_index(typeid(AviationStats)), [](const std::shared_ptr<EnemyStats>& enemyStats,
                                                const sf::Font& font,
                                                std::size_t level,
                                                std::size_t currentHP) {
        auto aviationStats = std::static_pointer_cast<AviationStats>(enemyStats);
        sf::Texture& texture = TextureManager::getTexture("gui/sprites/pictures/enemyAviationStats.png");
        sf::Sprite enemyStatsSprite;
        enemyStatsSprite.setTexture(texture);
        enemyStatsSprite.setPosition(0, 50);
        auto enemyStatsSpritePtr = std::make_shared<sf::Sprite>(enemyStatsSprite);
        std::vector<std::shared_ptr<sf::Drawable>> vector;
        vector.push_back(enemyStatsSpritePtr);

        auto levelTextPtr = createText(font, 13, sf::Color(64, 64, 64), 230, 93);
        levelTextPtr->setString(std::to_wstring(level));

        auto maxHPTextPtr = createText(font, 13, sf::Color(64, 64, 64), 230, 133);
        maxHPTextPtr->setString(std::to_wstring(aviationStats->maxHP_));

        auto currentHPTextPtr = createText(font, 13, sf::Color(64, 64, 64), 230, 176);
        currentHPTextPtr->setString(std::to_wstring(currentHP));

        auto regenerationRateTextPtr = createText(font, 13, sf::Color(64, 64, 64), 270, 216);
        regenerationRateTextPtr->setString(std::to_wstring(aviationStats->regenerationRate_));

        auto speedTextPtr = createText(font, 13, sf::Color(64, 64, 64), 285, 256);
        speedTextPtr->setString(std::to_wstring(aviationStats->speed_));

        auto ammoTextPtr = createText(font, 13, sf::Color(64, 64, 64), 170, 296);
        ammoTextPtr->setString(std::to_wstring(aviationStats->ammo_));

        vector.push_back(levelTextPtr);
        vector.push_back(maxHPTextPtr);
        vector.push_back(currentHPTextPtr);
        vector.push_back(regenerationRateTextPtr);
        vector.push_back(speedTextPtr);
        vector.push_back(ammoTextPtr);
        return vector; }},
    
    {std::type_index(typeid(LightInfantryStats)), [](const std::shared_ptr<EnemyStats>& enemyStats,
                                                     const sf::Font& font,
                                                     std::size_t level,
                                                     std::size_t currentHP) {
        auto lightStats = std::static_pointer_cast<LightInfantryStats>(enemyStats);
        sf::Texture& texture = TextureManager::getTexture("gui/sprites/pictures/enemyLightInfantryStats.png");
        sf::Sprite enemyStatsSprite;
        enemyStatsSprite.setTexture(texture);
        enemyStatsSprite.setPosition(0, 50);
        auto enemyStatsSpritePtr = std::make_shared<sf::Sprite>(enemyStatsSprite);
        std::vector<std::shared_ptr<sf::Drawable>> vector;
        vector.push_back(enemyStatsSpritePtr);

        auto levelTextPtr = createText(font, 13, sf::Color(64, 64, 64), 230, 93);
        levelTextPtr->setString(std::to_wstring(level));

        auto maxHPTextPtr = createText(font, 13, sf::Color(64, 64, 64), 230, 133);
        maxHPTextPtr->setString(std::to_wstring(lightStats->maxHP_));

        auto currentHPTextPtr = createText(font, 13, sf::Color(64, 64, 64), 230, 176);
        currentHPTextPtr->setString(std::to_wstring(currentHP));

        auto regenerationRateTextPtr = createText(font, 13, sf::Color(64, 64, 64), 270, 216);
        regenerationRateTextPtr->setString(std::to_wstring(lightStats->regenerationRate_));

        auto speedTextPtr = createText(font, 13, sf::Color(64, 64, 64), 285, 256);
        speedTextPtr->setString(std::to_wstring(lightStats->speed_));

        auto missChanceTextPtr = createText(font, 13, sf::Color(64, 64, 64), 200, 296);
        missChanceTextPtr->setString(std::to_wstring(lightStats->missChance_));

        vector.push_back(levelTextPtr);
        vector.push_back(maxHPTextPtr);
        vector.push_back(currentHPTextPtr);
        vector.push_back(regenerationRateTextPtr);
        vector.push_back(speedTextPtr);
        vector.push_back(missChanceTextPtr);
        return vector; }},

    {std::type_index(typeid(HeavyInfantryStats)), [](const std::shared_ptr<EnemyStats>& enemyStats,
                                                     const sf::Font& font,
                                                     std::size_t level,
                                                     std::size_t currentHP) {
        auto heavyStats = std::static_pointer_cast<HeavyInfantryStats>(enemyStats);
        sf::Texture& texture = TextureManager::getTexture("gui/sprites/pictures/enemyHeavyInfantryStats.png");
        sf::Sprite enemyStatsSprite;
        enemyStatsSprite.setTexture(texture);
        enemyStatsSprite.setPosition(0, 50);
        auto enemyStatsSpritePtr = std::make_shared<sf::Sprite>(enemyStatsSprite);
        std::vector<std::shared_ptr<sf::Drawable>> vector;
        vector.push_back(enemyStatsSpritePtr);

        auto levelTextPtr = createText(font, 13, sf::Color(64, 64, 64), 230, 100);
        levelTextPtr->setString(std::to_wstring(level));

        auto maxHPTextPtr = createText(font, 13, sf::Color(64, 64, 64), 230, 140);
        maxHPTextPtr->setString(std::to_wstring(heavyStats->maxHP_));

        auto currentHPTextPtr = createText(font, 13, sf::Color(64, 64, 64), 230, 180);
        currentHPTextPtr->setString(std::to_wstring(currentHP));

        auto regenerationRateTextPtr = createText(font, 13, sf::Color(64, 64, 64), 270, 223);
        regenerationRateTextPtr->setString(std::to_wstring(heavyStats->regenerationRate_));

        auto speedTextPtr = createText(font, 13, sf::Color(64, 64, 64), 285, 263);
        speedTextPtr->setString(std::to_wstring(heavyStats->speed_));

        auto damageTextPtr = createText(font, 13, sf::Color(64, 64, 64), 170, 303);
        damageTextPtr->setString(std::to_wstring(heavyStats->damage_));

        auto rangeTextPtr = createText(font, 13, sf::Color(64, 64, 64), 200, 343);
        rangeTextPtr->setString(std::to_wstring(heavyStats->range_));

        vector.push_back(levelTextPtr);
        vector.push_back(maxHPTextPtr);
        vector.push_back(currentHPTextPtr);
        vector.push_back(regenerationRateTextPtr);
        vector.push_back(speedTextPtr);
        vector.push_back(damageTextPtr);
        vector.push_back(rangeTextPtr);
        return vector; }},
    
    {std::type_index(typeid(HeroStats<AviationStats>)), [](const std::shared_ptr<EnemyStats>& enemyStats,
                                                     const sf::Font& font,
                                                     std::size_t level,
                                                     std::size_t currentHP) {
        auto heroAviationStats = std::static_pointer_cast<HeroStats<AviationStats>>(enemyStats);
        sf::Texture& texture = TextureManager::getTexture("gui/sprites/pictures/enemyHeroAviationStats.png");
        sf::Sprite enemyStatsSprite;
        enemyStatsSprite.setTexture(texture);
        enemyStatsSprite.setPosition(0, 50);
        auto enemyStatsSpritePtr = std::make_shared<sf::Sprite>(enemyStatsSprite);
        std::vector<std::shared_ptr<sf::Drawable>> vector;
        vector.push_back(enemyStatsSpritePtr);

        auto levelTextPtr = createText(font, 13, sf::Color(64, 64, 64), 230, 100);
        levelTextPtr->setString(std::to_wstring(level));

        auto maxHPTextPtr = createText(font, 13, sf::Color(64, 64, 64), 230, 140);
        maxHPTextPtr->setString(std::to_wstring(heroAviationStats->maxHP_));

        auto currentHPTextPtr = createText(font, 13, sf::Color(64, 64, 64), 230, 180);
        currentHPTextPtr->setString(std::to_wstring(currentHP));

        auto regenerationRateTextPtr = createText(font, 13, sf::Color(64, 64, 64), 270, 223);
        regenerationRateTextPtr->setString(std::to_wstring(heroAviationStats->regenerationRate_));

        auto speedTextPtr = createText(font, 13, sf::Color(64, 64, 64), 285, 263);
        speedTextPtr->setString(std::to_wstring(heroAviationStats->speed_));

        auto ammoTextPtr = createText(font, 13, sf::Color(64, 64, 64), 170, 303);
        ammoTextPtr->setString(std::to_wstring(heroAviationStats->ammo_));

        auto auraRadiusTextPtr = createText(font, 13, sf::Color(64, 64, 64), 200, 343);
        auraRadiusTextPtr->setString(std::to_wstring(heroAviationStats->auraRadius_));

        vector.push_back(levelTextPtr);
        vector.push_back(maxHPTextPtr);
        vector.push_back(currentHPTextPtr);
        vector.push_back(regenerationRateTextPtr);
        vector.push_back(speedTextPtr);
        vector.push_back(ammoTextPtr);
        vector.push_back(auraRadiusTextPtr);
        return vector; }},
    
    {std::type_index(typeid(HeroStats<LightInfantryStats>)), [](const std::shared_ptr<EnemyStats>& enemyStats,
                                                     const sf::Font& font,
                                                     std::size_t level,
                                                     std::size_t currentHP) {
        auto heroLightStats = std::static_pointer_cast<HeroStats<LightInfantryStats>>(enemyStats);
        sf::Texture& texture = TextureManager::getTexture("gui/sprites/pictures/enemyHeroLightInfantryStats.png");
        sf::Sprite enemyStatsSprite;
        enemyStatsSprite.setTexture(texture);
        enemyStatsSprite.setPosition(0, 50);
        auto enemyStatsSpritePtr = std::make_shared<sf::Sprite>(enemyStatsSprite);
        std::vector<std::shared_ptr<sf::Drawable>> vector;
        vector.push_back(enemyStatsSpritePtr);

        auto levelTextPtr = createText(font, 13, sf::Color(64, 64, 64), 230, 100);
        levelTextPtr->setString(std::to_wstring(level));

        auto maxHPTextPtr = createText(font, 13, sf::Color(64, 64, 64), 230, 140);
        maxHPTextPtr->setString(std::to_wstring(heroLightStats->maxHP_));

        auto currentHPTextPtr = createText(font, 13, sf::Color(64, 64, 64), 230, 180);
        currentHPTextPtr->setString(std::to_wstring(currentHP));

        auto regenerationRateTextPtr = createText(font, 13, sf::Color(64, 64, 64), 270, 223);
        regenerationRateTextPtr->setString(std::to_wstring(heroLightStats->regenerationRate_));

        auto speedTextPtr = createText(font, 13, sf::Color(64, 64, 64), 285, 263);
        speedTextPtr->setString(std::to_wstring(heroLightStats->speed_));

        auto missChanceTextPtr = createText(font, 13, sf::Color(64, 64, 64), 200, 303);
        missChanceTextPtr->setString(std::to_wstring(heroLightStats->missChance_));

        auto auraRadiusTextPtr = createText(font, 13, sf::Color(64, 64, 64), 200, 343);
        auraRadiusTextPtr->setString(std::to_wstring(heroLightStats->auraRadius_));

        vector.push_back(levelTextPtr);
        vector.push_back(maxHPTextPtr);
        vector.push_back(currentHPTextPtr);
        vector.push_back(regenerationRateTextPtr);
        vector.push_back(speedTextPtr);
        vector.push_back(missChanceTextPtr);
        vector.push_back(auraRadiusTextPtr);
        return vector; }},

    {std::type_index(typeid(HeroStats<HeavyInfantryStats>)), [](const std::shared_ptr<EnemyStats>& enemyStats,
                                                     const sf::Font& font,
                                                     std::size_t level,
                                                     std::size_t currentHP) {
        auto heroHeavyStats = std::static_pointer_cast<HeroStats<HeavyInfantryStats>>(enemyStats);
        sf::Texture& texture = TextureManager::getTexture("gui/sprites/pictures/enemyHeroHeavyInfantryStats.png");
        sf::Sprite enemyStatsSprite;
        enemyStatsSprite.setTexture(texture);
        enemyStatsSprite.setPosition(0, 50);
        auto enemyStatsSpritePtr = std::make_shared<sf::Sprite>(enemyStatsSprite);
        std::vector<std::shared_ptr<sf::Drawable>> vector;
        vector.push_back(enemyStatsSpritePtr);

        auto levelTextPtr = createText(font, 13, sf::Color(64, 64, 64), 230, 107);
        levelTextPtr->setString(std::to_wstring(level));

        auto maxHPTextPtr = createText(font, 13, sf::Color(64, 64, 64), 230, 147);
        maxHPTextPtr->setString(std::to_wstring(heroHeavyStats->maxHP_));

        auto currentHPTextPtr = createText(font, 13, sf::Color(64, 64, 64), 230, 187);
        currentHPTextPtr->setString(std::to_wstring(currentHP));

        auto regenerationRateTextPtr = createText(font, 13, sf::Color(64, 64, 64), 270, 227);
        regenerationRateTextPtr->setString(std::to_wstring(heroHeavyStats->regenerationRate_));

        auto speedTextPtr = createText(font, 13, sf::Color(64, 64, 64), 285, 269);
        speedTextPtr->setString(std::to_wstring(heroHeavyStats->speed_));

        auto damageTextPtr = createText(font, 13, sf::Color(64, 64, 64), 170, 309);
        damageTextPtr->setString(std::to_wstring(heroHeavyStats->damage_));

        auto rangeTextPtr = createText(font, 13, sf::Color(64, 64, 64), 230, 349);
        rangeTextPtr->setString(std::to_wstring(heroHeavyStats->range_));

        auto auraRadiusTextPtr = createText(font, 13, sf::Color(64, 64, 64), 200, 389);
        auraRadiusTextPtr->setString(std::to_wstring(heroHeavyStats->auraRadius_));

        vector.push_back(levelTextPtr);
        vector.push_back(maxHPTextPtr);
        vector.push_back(currentHPTextPtr);
        vector.push_back(regenerationRateTextPtr);
        vector.push_back(speedTextPtr);
        vector.push_back(damageTextPtr);
        vector.push_back(rangeTextPtr);
        vector.push_back(auraRadiusTextPtr);
        return vector; }}
};


std::unordered_map<std::type_index,
                   std::function<std::vector<std::shared_ptr<sf::Drawable>>(const std::shared_ptr<StructureStats>& structureStats,
                                                                            const sf::Font& font,
                                                                            std::size_t level)>> GameRenderer::createVisualStructureStatsTable_ = {
    {std::type_index(typeid(WallStats)), [](const std::shared_ptr<StructureStats>& structureStats,
                                       const sf::Font& font,
                                       std::size_t level) {
        auto wallStats = std::static_pointer_cast<WallStats>(structureStats);
        sf::Texture& texture = TextureManager::getTexture("gui/sprites/pictures/structureWallStats.png");
        sf::Sprite structureStatsSprite;
        structureStatsSprite.setTexture(texture);
        structureStatsSprite.setPosition(0, 50);
        auto structureStatsSpritePtr = std::make_shared<sf::Sprite>(structureStatsSprite);
        std::vector<std::shared_ptr<sf::Drawable>> vector;
        vector.push_back(structureStatsSpritePtr);

        auto levelTextPtr = createText(font, 13, sf::Color(64, 64, 64), 230, 80);
        levelTextPtr->setString(std::to_wstring(level));

        auto upgradeCostTextPtr = createText(font, 13, sf::Color(64, 64, 64), 260, 120);
        upgradeCostTextPtr->setString(std::to_wstring(wallStats->upgradeCost_));

        auto maxHPTextPtr = createText(font, 13, sf::Color(64, 64, 64), 230, 163);
        maxHPTextPtr->setString(std::to_wstring(wallStats->maxHP_));

        auto currentHPTextPtr = createText(font, 13, sf::Color(64, 64, 64), 230, 203);
        currentHPTextPtr->setString(std::to_wstring(wallStats->currentHP_));

        vector.push_back(levelTextPtr);
        vector.push_back(upgradeCostTextPtr);
        vector.push_back(maxHPTextPtr);
        vector.push_back(currentHPTextPtr);
        return vector; }},

    {std::type_index(typeid(TowerStats)), [](const std::shared_ptr<StructureStats>& structureStats,
                                       const sf::Font& font,
                                       std::size_t level) {
        auto towerStats = std::static_pointer_cast<TowerStats>(structureStats);

        sf::Texture& texture = TextureManager::getTexture("gui/sprites/pictures/structureTowerStats.png");
        sf::Sprite structureStatsSprite;
        structureStatsSprite.setTexture(texture);
        structureStatsSprite.setPosition(0, 50);
        auto structureStatsSpritePtr = std::make_shared<sf::Sprite>(structureStatsSprite);
        std::vector<std::shared_ptr<sf::Drawable>> vector;
        vector.push_back(structureStatsSpritePtr);

        auto levelTextPtr = createText(font, 13, sf::Color(64, 64, 64), 230, 83);
        levelTextPtr->setString(std::to_wstring(level));

        auto upgradeCostTextPtr = createText(font, 13, sf::Color(64, 64, 64), 260, 123);
        upgradeCostTextPtr->setString(std::to_wstring(towerStats->upgradeCost_));

        auto rangeTextPtr = createText(font, 13, sf::Color(64, 64, 64), 230, 163);
        rangeTextPtr->setString(std::to_wstring(towerStats->range_));

        auto damageTextPtr = createText(font, 13, sf::Color(64, 64, 64), 230, 206);
        damageTextPtr->setString(std::to_wstring(towerStats->damage_));

        auto firerateTextPtr = createText(font, 13, sf::Color(64, 64, 64), 230, 246);
        firerateTextPtr->setString(std::to_wstring(towerStats->fireRate_));

        vector.push_back(levelTextPtr);
        vector.push_back(upgradeCostTextPtr);
        vector.push_back(rangeTextPtr);
        vector.push_back(damageTextPtr);
        vector.push_back(firerateTextPtr);
        return vector; }},
    
    {std::type_index(typeid(CastleStats)), [](const std::shared_ptr<StructureStats>& structureStats,
                                       const sf::Font& font,
                                       std::size_t level) {
        auto castleStats = std::static_pointer_cast<CastleStats>(structureStats);

        sf::Texture& texture = TextureManager::getTexture("gui/sprites/pictures/structureCastleStats.png");
        sf::Sprite structureStatsSprite;
        structureStatsSprite.setTexture(texture);
        structureStatsSprite.setPosition(0, 50);
        auto structureStatsSpritePtr = std::make_shared<sf::Sprite>(structureStatsSprite);
        std::vector<std::shared_ptr<sf::Drawable>> vector;
        vector.push_back(structureStatsSpritePtr);

        auto levelTextPtr = createText(font, 13, sf::Color(64, 64, 64), 230, 83);
        levelTextPtr->setString(std::to_wstring(level));

        auto upgradeCostTextPtr = createText(font, 13, sf::Color(64, 64, 64), 260, 123);
        upgradeCostTextPtr->setString(std::to_wstring(castleStats->upgradeCost_));

        auto profitTextPtr = createText(font, 13, sf::Color(64, 64, 64), 230, 163);
        profitTextPtr->setString(std::to_wstring(castleStats->profit_));

        auto maxHPTextPtr = createText(font, 13, sf::Color(64, 64, 64), 230, 206);
        maxHPTextPtr->setString(std::to_wstring(castleStats->maxHP_));

        auto currentHPTextPtr = createText(font, 13, sf::Color(64, 64, 64), 230, 246);
        currentHPTextPtr->setString(std::to_wstring(castleStats->currentHP_));

        auto repairSpeedTextPtr = createText(font, 13, sf::Color(64, 64, 64), 230, 286);
        repairSpeedTextPtr->setString(std::to_wstring(castleStats->repairSpeed_));

        vector.push_back(levelTextPtr);
        vector.push_back(upgradeCostTextPtr);
        vector.push_back(profitTextPtr);
        vector.push_back(maxHPTextPtr);
        vector.push_back(currentHPTextPtr);
        vector.push_back(repairSpeedTextPtr);
        return vector; }},

    {std::type_index(typeid(LairStats)), [](const std::shared_ptr<StructureStats>& structureStats,
                                       const sf::Font& font,
                                       std::size_t level) {

        sf::Texture& texture = TextureManager::getTexture("gui/sprites/pictures/structureLairStats.png");
        sf::Sprite structureStatsSprite;
        structureStatsSprite.setTexture(texture);
        structureStatsSprite.setPosition(0, 50);
        auto structureStatsSpritePtr = std::make_shared<sf::Sprite>(structureStatsSprite);
        std::vector<std::shared_ptr<sf::Drawable>> vector;
        vector.push_back(structureStatsSpritePtr);

        auto levelTextPtr = createText(font, 13, sf::Color(64, 64, 64), 230, 73);
        levelTextPtr->setString(std::to_wstring(level));

        auto upgradeCostTextPtr = createText(font, 13, sf::Color(64, 64, 64), 260, 113);
        upgradeCostTextPtr->setString(std::to_wstring(structureStats->upgradeCost_));

        vector.push_back(levelTextPtr);
        vector.push_back(upgradeCostTextPtr);
        return vector; }}
};


std::shared_ptr<sf::Text> GameRenderer::createText(const sf::Font& font,
                                     std::size_t charSize,
                                     sf::Color color,
                                     std::size_t posX,
                                     std::size_t posY) {
    auto text = std::make_shared<sf::Text>();
    text->setFont(font);
    text->setCharacterSize(charSize);
    text->setPosition(posX, posY);
    text->setFillColor(color);
    return text;
}