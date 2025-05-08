#include <gtest/gtest.h>
#include "tower.h"
#include "lair.h"
#include "structureFactory.h"
#include "game.h"

TEST(TowerTests, dealDamage) {
    Game game{};
    game.initGame("/home/gkasp/oop2024/3/tests/configs/");
    auto structure = game.getLandscape()->getStructureByPosition({4,9});
    auto tower = std::static_pointer_cast<Tower>(structure);
    EXPECT_NO_THROW(tower->dealDamage());
    EXPECT_EQ(tower->dealDamage(), 30);
}


TEST(TowerTests, levelUp) {
    Game game{};
    game.initGame("/home/gkasp/oop2024/3/tests/configs/");
    auto structure = game.getLandscape()->getStructureByPosition({4,9});
    auto tower = std::static_pointer_cast<Tower>(structure);
    auto prevLevel = tower->getLevel();
    EXPECT_NO_THROW(tower->levelUp());
    auto newLevel = tower->getLevel();
    EXPECT_EQ(tower->getLevel(), newLevel);
    EXPECT_NE(tower->getLevel(), prevLevel);
}


TEST(TowerTests, makeMove) {
    Game game{};
    game.initGame("/home/gkasp/oop2024/3/tests/configs/");
    auto structure = game.getLandscape()->getStructureByPosition({4,9});
    auto tower = std::static_pointer_cast<Tower>(structure);

    auto lairStructure = game.getLandscape()->getStructureByPosition({0,0});
    auto lair = std::static_pointer_cast<Lair>(lairStructure);

    auto enemy = lair->releaseEnemy("Aviation", 1);
    game.getLandscape()->setEnemyByPosition({4,8}, enemy);

    std::size_t newHP = enemy->getCurrentHP() - tower->dealDamage();

    EXPECT_NO_THROW(tower->makeMove());
    EXPECT_EQ(enemy->getCurrentHP(), newHP);
}