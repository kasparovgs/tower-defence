#include <gtest/gtest.h>
#include "heavyInfantry.h"
#include "castle.h"
#include "game.h"
#include <random>

TEST(HeavyInfantryTests, Constructor){
    EXPECT_NO_THROW(HeavyInfantry enemy("abc", 10, 11, 12, {0, 1}, 13, 14, 15));
    std::pair<int, int> pos = {0, 1};
    auto enemy = std::make_shared<HeavyInfantry>("abc", 11, 12, 13, pos, 1, 2, 3);
    EXPECT_EQ("abc", enemy->getName());
    EXPECT_EQ(11, enemy->getMaxHP());
    EXPECT_EQ(12, enemy->getCurrentHP());
    EXPECT_EQ(13, enemy->getRegenerationRate());
    EXPECT_EQ(pos, enemy->getPosition());
    EXPECT_EQ(1, enemy->getSpeed());
    EXPECT_EQ(2, enemy->getDamage());
    EXPECT_EQ(3, enemy->getRange());
}


TEST(HeavyInfantryTests, findPath){
    auto landscape = std::make_shared<Landscape>();
    landscape->changeFieldFromCSV("/home/gkasp/oop2024/3/tests/configs/");
    landscape->changeStructuresFromCSV("/home/gkasp/oop2024/3/tests/configs/");
    auto enemy = std::static_pointer_cast<Enemy>(std::make_shared<HeavyInfantry>());
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


TEST(HeavyInfantryTests, takeDamage){
    std::size_t maxHP = genRandomNum();
    auto diff = maxHP / 2;
    HeavyInfantry enemy("abc", maxHP, maxHP, 13, {0, 1}, 1, 2, 3);
    EXPECT_NO_THROW(enemy.takeDamage(diff));
    EXPECT_EQ(enemy.getCurrentHP(), maxHP - diff);
    EXPECT_NO_THROW(enemy.takeDamage(maxHP));
    EXPECT_EQ(enemy.getCurrentHP(), 0);
}

TEST(HeavyInfantryTests, makeMove) {
    Game game{};
    game.initGame("/home/gkasp/oop2024/3/tests/configs/");
    HeavyInfantry enemy("abc", 1000, 1000, 10, {0, 0}, 1, 200, 5);
    enemy.setLandscape(game.getLandscape()->getSelf());
    enemy.findPath();

    for (std::size_t i = 0; i < enemy.getPath().size() - 1; i++) {
        EXPECT_NO_THROW(enemy.makeMove());
    }
    EXPECT_EQ(enemy.getLandscape()->getStructureByPosition({5,3})->getValidity(), false);
    EXPECT_EQ(enemy.getLandscape()->getStructureByPosition({5,4})->getValidity(), false);
}