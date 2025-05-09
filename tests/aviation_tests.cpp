#include <gtest/gtest.h>
#include <climits>
#include "aviation.h"
#include "game.h"
#include "wall.h"
#include "castle.h"
#include <random>

TEST(AviationTests, Constructor) {
    EXPECT_NO_THROW(Aviation enemy("abc", 11, 12, 13, {0, 1}, 1, 2));
    std::pair<int, int> pos = {0, 1};
    auto enemy = std::make_shared<Aviation>("abc", 11, 12, 13, pos, 1, 2);
    EXPECT_EQ("abc", enemy->getName());
    EXPECT_EQ(11, enemy->getMaxHP());
    EXPECT_EQ(12, enemy->getCurrentHP());
    EXPECT_EQ(13, enemy->getRegenerationRate());
    EXPECT_EQ(pos, enemy->getPosition());
    EXPECT_EQ(1, enemy->getSpeed());
    EXPECT_EQ(2, enemy->getAmmo());
}


TEST(AviationTests, findPath) {
    auto landscape = std::make_shared<Landscape>();
    landscape->changeFieldFromCSV("tests/configs/");
    landscape->changeStructuresFromCSV("tests/configs/");
    auto enemy = std::static_pointer_cast<Enemy>(std::make_shared<Aviation>());
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


TEST(AviationTests, dealDamage) {
    Aviation enemy("abc", 10, 10, 10, {0, 1}, 1, 2);
    EXPECT_NO_THROW(enemy.dealDamage());
    EXPECT_EQ(enemy.dealDamage(), INT_MAX);
}


static std::size_t genRandomNum() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<std::size_t> dis(100, 10000);
    return dis(gen);
}


TEST(AviationTests, takeDamage) {
    std::size_t maxHP = genRandomNum();
    auto diff = maxHP / 2;
    Aviation enemy("abc", maxHP, maxHP, 10, {0, 1}, 1, 2);
    EXPECT_NO_THROW(enemy.takeDamage(diff));
    EXPECT_EQ(enemy.getCurrentHP(), maxHP - diff);
    EXPECT_NO_THROW(enemy.takeDamage(maxHP));
    EXPECT_EQ(enemy.getCurrentHP(), 0);
}


TEST(AviationTests, makeMove) {
    Game game{};
    game.initGame("tests/configs/");
    Aviation enemy("abc", 1000, 1000, 10, {0, 0}, 1, 5);
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