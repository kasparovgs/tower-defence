#include <gtest/gtest.h>
#include "wall.h"
#include "game.h"
#include "structureFactory.h"

TEST(WallTests, levelUp) {
    Game game{};
    game.initGame("/home/gkasp/oop2024/3/tests/configs/");
    auto structure = game.getLandscape()->getStructureByPosition({5, 3});
    auto wall = std::static_pointer_cast<Wall>(structure);

    auto prevLevel = wall->getLevel();
    auto prevMaxHP = wall->getMaxHP();
    auto prevCurrentHP = wall->getCurrentHP();
    EXPECT_NO_THROW(wall->levelUp());

    EXPECT_NE(prevMaxHP, wall->getMaxHP());

    auto stats = StructureFactory::StructuresStatsTable_["Wall"][prevLevel];
    auto wallStats = std::static_pointer_cast<WallStats>(stats);

    EXPECT_EQ(wall->getCurrentHP(), prevCurrentHP);
    EXPECT_EQ(wallStats->maxHP_, wall->getMaxHP());
    EXPECT_EQ(prevLevel + 1, wall->getLevel());
}