#include <gtest/gtest.h>
#include "hero.h"
#include "game.h"
#include "lair.h"
#include <random>

TEST(HeroTests, findPathAviation){
    auto landscape = std::make_shared<Landscape>();
    landscape->changeFieldFromCSV("tests/configs/");
    landscape->changeStructuresFromCSV("tests/configs/");
    auto enemy = std::static_pointer_cast<Enemy>(std::make_shared<Hero<Aviation>>());
    enemy->setLandscape(landscape);
    enemy->findPath();
    auto path = enemy->getPath();
    // for (const auto& pos : path){
    //         std::cout << "(" << pos.first << ", " << pos.second << ") " << std::endl;
    // }
    std::vector<std::pair<int, int>> expPath = {{0, 0}, {0, 1}, {0, 2}, {0, 3}, {1, 3}, {2, 3}, {3, 3}, {4, 3},
                                                  {5, 3}, {5, 4}, {6, 4}, {6, 5}, {7, 5}, {8, 5}, 
                                                  {9, 5}, {9, 4}, {9, 3}, {9, 2}, {9, 1}, {9, 0}, 
                                                  {8, 0}, {7, 0}, {7, 1}, {7, 2}, {7, 3}};
    EXPECT_EQ(path, expPath);
}


TEST(HeroTests, findPathLightInfantry){
    auto landscape = std::make_shared<Landscape>();
    landscape->changeFieldFromCSV("tests/configs/");
    landscape->changeStructuresFromCSV("tests/configs/");
    auto enemy = std::static_pointer_cast<Enemy>(std::make_shared<Hero<LightInfantry>>());
    enemy->setLandscape(landscape);
    enemy->findPath();
    auto path = enemy->getPath();
    // for (const auto& pos : path){
    //         std::cout << "(" << pos.first << ", " << pos.second << ") " << std::endl;
    // }
    std::vector<std::pair<int, int>> expPath = {{0, 0}, {0, 1}, {0, 2}, {0, 3}, {1, 3}, {2, 3}, {2, 4}, {2, 5}, {2, 6}, {2, 7}, {2, 8},
                                                {3, 8}, {4, 8}, {5, 8}, {6, 8}, {7, 8}, {7, 7}, {7, 6}, {7, 5}, {8, 5}, {9, 5},
                                                {9, 4},{9, 3}, {9, 2}, {9, 1}, {9, 0}, {8, 0}, {7, 0}, {7, 1}, {7, 2}, {7, 3}};
    EXPECT_EQ(path, expPath);
}


TEST(HeroTests, findPathHeavyInfantry){
    auto landscape = std::make_shared<Landscape>();
    landscape->changeFieldFromCSV("tests/configs/");
    landscape->changeStructuresFromCSV("tests/configs/");
    auto enemy = std::static_pointer_cast<Enemy>(std::make_shared<Hero<HeavyInfantry>>());
    enemy->setLandscape(landscape);
    enemy->findPath();
    auto path = enemy->getPath();
    // for (const auto& pos : path){
    //         std::cout << "(" << pos.first << ", " << pos.second << ") " << std::endl;
    // }
    std::vector<std::pair<int, int>> expPath = {{0, 0}, {0, 1}, {0, 2}, {0, 3}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3}, {5, 4}, {6, 4}, {6, 5}, {7, 5}, {8, 5}, {9, 5},
                                                {9, 4},{9, 3}, {9, 2}, {9, 1}, {9, 0}, {8, 0}, {7, 0}, {7, 1}, {7, 2}, {7, 3}};
    EXPECT_EQ(path, expPath);
}


static std::size_t genRandomNum(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<std::size_t> dis(100, 10000);
    return dis(gen);
}


TEST(HeroTests, takeDamage){
    auto enemyHI = std::static_pointer_cast<Enemy>(std::make_shared<Hero<HeavyInfantry>>());
    auto enemyLI = std::static_pointer_cast<Enemy>(std::make_shared<Hero<LightInfantry>>());
    auto enemyA = std::static_pointer_cast<Enemy>(std::make_shared<Hero<Aviation>>());
    std::size_t maxHP = genRandomNum();
    enemyHI->setCurrentHP(maxHP);
    enemyLI->setCurrentHP(maxHP);
    enemyA->setCurrentHP(maxHP);
    auto diff = maxHP / 2;

    EXPECT_NO_THROW(enemyHI->takeDamage(diff));
    EXPECT_EQ(enemyHI->getCurrentHP(), maxHP - diff);
    EXPECT_NO_THROW(enemyHI->takeDamage(maxHP));
    EXPECT_EQ(enemyHI->getCurrentHP(), 0);

    EXPECT_NO_THROW(enemyLI->takeDamage(diff));
    EXPECT_EQ(enemyLI->getCurrentHP(), maxHP - diff);
    EXPECT_NO_THROW(enemyLI->takeDamage(maxHP));
    EXPECT_EQ(enemyLI->getCurrentHP(), 0);

    EXPECT_NO_THROW(enemyA->takeDamage(diff));
    EXPECT_EQ(enemyA->getCurrentHP(), maxHP - diff);
    EXPECT_NO_THROW(enemyA->takeDamage(maxHP));
    EXPECT_EQ(enemyA->getCurrentHP(), 0);
}


TEST(HeroTests, aurasApplyingAndRemoving) {
    Game game{};
    game.initGame("tests/configs/");
    auto structure = game.getLandscape()->getStructureByPosition({0, 0});
    auto lair = std::static_pointer_cast<Lair>(structure);
    auto hero = lair->releaseEnemy("HeroHeavyInfantry", 4);

    auto enemy = lair->releaseEnemy("Aviation", 4);
    auto prevHP = enemy->getMaxHP();
    auto prevSpeed = enemy->getSpeed();
    auto prevRegen = enemy->getRegenerationRate();
    game.getLandscape()->setEnemyByPosition({1, 1}, enemy);
    game.getLandscape()->setEnemyByPosition({3, 1}, hero);
    enemy->setPosition({1, 1});
    hero->setPosition({3, 1});
    hero->setLandscape(game.getLandscape()->getSelf());
    hero->findPath();
    hero->makeMove();
    EXPECT_EQ(enemy->getMaxHP(), prevHP + 100);
    EXPECT_EQ(enemy->getSpeed(), prevSpeed + 2);
    EXPECT_EQ(enemy->getRegenerationRate(), prevRegen + 3);

    // удаление
    game.getLandscape()->setEnemyByPosition({3, 1}, nullptr);
    hero->setPosition({9, 3});
    game.getLandscape()->setEnemyByPosition({9, 3}, hero);
    hero->makeMove();
    hero->setCurrentStep(16);
    EXPECT_EQ(enemy->getMaxHP(), prevHP);
    EXPECT_EQ(enemy->getSpeed(), prevSpeed);
    EXPECT_EQ(enemy->getRegenerationRate(), prevRegen);
}


TEST(HeroTests, destructor) {
    Game game{};
    game.initGame("tests/configs/");
    auto structure = game.getLandscape()->getStructureByPosition({0, 0});
    auto lair = std::static_pointer_cast<Lair>(structure);
    auto enemy = lair->releaseEnemy("Aviation", 4);
    {
    auto hero = lair->releaseEnemy("HeroHeavyInfantry", 4);

    auto prevHP = enemy->getMaxHP();
    auto prevSpeed = enemy->getSpeed();
    auto prevRegen = enemy->getRegenerationRate();
    game.getLandscape()->setEnemyByPosition({1, 1}, enemy);
    game.getLandscape()->setEnemyByPosition({3, 1}, hero);
    enemy->setPosition({1, 1});
    hero->setPosition({3, 1});
    hero->setLandscape(game.getLandscape()->getSelf());
    hero->findPath();
    hero->makeMove();
    auto exHero = std::static_pointer_cast<Hero<HeavyInfantry>>(hero);
    auto vecAffOn = exHero->getAuras()[0]->getAffectOn();
    EXPECT_EQ(enemy->getMaxHP(), prevHP + 100);
    EXPECT_EQ(enemy->getSpeed(), prevSpeed + 2);
    EXPECT_EQ(enemy->getRegenerationRate(), prevRegen + 3);
    }
    enemy->setLandscape(game.getLandscape()->getSelf());
    enemy->findPath();
    enemy->makeMove();
}