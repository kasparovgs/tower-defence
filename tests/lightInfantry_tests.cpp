#include <gtest/gtest.h>
#include "lightInfantry.h"
#include "castle.h"
#include "game.h"
#include <random>

TEST(LightInfantryTests, Constructor){
    EXPECT_NO_THROW(LightInfantry enemy("abc", 10, 11, 12, {0, 1}, 13, 14));
    std::pair<int, int> pos = {0, 1};
    auto enemy = std::make_shared<LightInfantry>("abc", 11, 12, 13, pos, 1, 2);
    EXPECT_EQ("abc", enemy->getName());
    EXPECT_EQ(11, enemy->getMaxHP());
    EXPECT_EQ(12, enemy->getCurrentHP());
    EXPECT_EQ(13, enemy->getRegenerationRate());
    EXPECT_EQ(pos, enemy->getPosition());
    EXPECT_EQ(1, enemy->getSpeed());
    EXPECT_EQ(2, enemy->getMissChance());
}

TEST(LightInfantryTests, findPath){
    auto landscape = std::make_shared<Landscape>();
    landscape->changeFieldFromCSV("tests/configs/");
    landscape->changeStructuresFromCSV("tests/configs/");
    auto enemy = std::static_pointer_cast<Enemy>(std::make_shared<LightInfantry>());
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


static std::size_t genRandomNum(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<std::size_t> dis(100, 10000);
    return dis(gen);
}


TEST(LightInfantryTests, takeDamage){
    auto maxHP = genRandomNum();
    LightInfantry enemy("abc", maxHP, maxHP, 12, {0, 1}, 13, 100);
    std::size_t diff = maxHP / 2;
    EXPECT_NO_THROW(enemy.takeDamage(diff));
    EXPECT_EQ(enemy.getCurrentHP(), maxHP);

    LightInfantry enemy1("abc", maxHP, maxHP, 12, {0, 1}, 13, 0);

    EXPECT_NO_THROW(enemy1.takeDamage(diff));
    EXPECT_EQ(enemy1.getCurrentHP(), maxHP - diff);
    EXPECT_NO_THROW(enemy1.takeDamage(maxHP));
    EXPECT_EQ(enemy1.getCurrentHP(), 0);
}


TEST(LightInfantryTests, makeMove) {
    Game game{};
    game.initGame("tests/configs/");
    LightInfantry enemy("abc", 1000, 1000, 10, {0, 0}, 1, 5);
    enemy.setLandscape(game.getLandscape()->getSelf());
    enemy.findPath();
    auto structure = enemy.getLandscape()->getStructureByPosition({7,3});
    auto castle = std::static_pointer_cast<Castle>(structure);
    std::size_t castlePrevHP = castle->getCurrentHP();
    for (std::size_t i = 0; i < enemy.getPath().size() - 1; i++) {
        EXPECT_NO_THROW(enemy.makeMove());
    }
    std::size_t castleNewHP = castle->getCurrentHP();
    EXPECT_LT(castleNewHP, castlePrevHP);
}