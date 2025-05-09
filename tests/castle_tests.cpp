#include <gtest/gtest.h>
#include "castle.h"
#include "game.h"
#include "structureFactory.h"

TEST(CastleTests, levelUp) {
    Game game{};
    game.initGame("tests/configs/");
    auto castlePos = game.getLandscape()->getCastlePosition();
    auto structure = game.getLandscape()->getStructureByPosition(castlePos);
    auto castle = std::static_pointer_cast<Castle>(structure);

    auto prevLevel = castle->getLevel();
    auto prevProfit = castle->getProfit();
    auto prevRepairSpeed = castle->getRepairSpeed();
    auto prevMaxHP = castle->getMaxHP();

    EXPECT_NO_THROW(castle->levelUp());

    EXPECT_NE(prevProfit, castle->getProfit());
    EXPECT_NE(prevRepairSpeed, castle->getRepairSpeed());
    EXPECT_NE(prevMaxHP, castle->getMaxHP());

    auto stats = StructureFactory::StructuresStatsTable_["Castle"][prevLevel];
    auto castleStats = std::static_pointer_cast<CastleStats>(stats);

    EXPECT_EQ(castleStats->profit_, castle->getProfit());
    EXPECT_EQ(castleStats->repairSpeed_, castle->getRepairSpeed());
    EXPECT_EQ(castleStats->maxHP_,castle->getMaxHP());
    EXPECT_EQ(prevLevel + 1, castle->getLevel());
}


TEST(CastleTests, collectAccumulatedGold) {
    Game game{};
    game.initGame("tests/configs/");
    auto castlePos = game.getLandscape()->getCastlePosition();
    auto structure = game.getLandscape()->getStructureByPosition(castlePos);
    auto castle = std::static_pointer_cast<Castle>(structure);

    auto stats = StructureFactory::StructuresStatsTable_["Castle"][castle->getLevel() - 1];
    auto castleStats = std::static_pointer_cast<CastleStats>(stats);

    castle->makeMove();
    auto gold = castle->collectAccumulatedGold();
    EXPECT_EQ(gold, castleStats->profit_);
    EXPECT_EQ(castle->getAccumulatedGold(), 0);
}


TEST(CastleTests, makeMove) {
    Game game{};
    game.initGame("tests/configs/");
    auto castlePos = game.getLandscape()->getCastlePosition();
    auto structure = game.getLandscape()->getStructureByPosition(castlePos);
    auto castle = std::static_pointer_cast<Castle>(structure);

    auto stats = StructureFactory::StructuresStatsTable_["Castle"][castle->getLevel() - 1];
    auto castleStats = std::static_pointer_cast<CastleStats>(stats);

    EXPECT_NO_THROW(castle->makeMove());
    std::size_t damage = 100;
    std::size_t gold = castle->getAccumulatedGold();
    castle->takeDamage(damage);

    std::size_t hp = castle->getCurrentHP();
    castle->makeMove();
    EXPECT_EQ(hp + castleStats->repairSpeed_, castle->getCurrentHP());
    EXPECT_EQ(gold + castleStats->profit_, castle->getAccumulatedGold());
}