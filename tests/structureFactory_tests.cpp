#include <gtest/gtest.h>
#include "structureFactory.h"
#include "tower.h"
#include "castle.h"
#include "wall.h"
#include "lair.h"

TEST(StructureFactoryTests, loadStatsFromConfig){
    EXPECT_NO_THROW(StructureFactory::loadStatsFromConfig("tests/configs/structuresStats_config.csv"));
    StructureFactory::loadStatsFromConfig("tests/configs/structuresStats_config.csv");
    auto wallStats = StructureFactory::StructuresStatsTable_["Wall"];
    EXPECT_EQ(std::static_pointer_cast<WallStats>(wallStats[0])->upgradeCost_, 300);
    EXPECT_EQ(std::static_pointer_cast<WallStats>(wallStats[1])->maxHP_, 700);

    auto towerStats = StructureFactory::StructuresStatsTable_["Tower"];

    EXPECT_EQ(std::static_pointer_cast<TowerStats>(towerStats[3])->upgradeCost_, 1100);
    EXPECT_EQ(std::static_pointer_cast<TowerStats>(towerStats[2])->range_, 4);
    EXPECT_EQ(std::static_pointer_cast<TowerStats>(towerStats[2])->damage_, 75);

    auto castleStats = StructureFactory::StructuresStatsTable_["Castle"];
    EXPECT_EQ(std::static_pointer_cast<CastleStats>(castleStats[1])->upgradeCost_, 7000);
    EXPECT_EQ(std::static_pointer_cast<CastleStats>(castleStats[1])->maxHP_, 6000);
    EXPECT_EQ(std::static_pointer_cast<CastleStats>(castleStats[1])->repairSpeed_, 5);
    EXPECT_EQ(std::static_pointer_cast<CastleStats>(castleStats[1])->profit_, 60);

    auto lairStats = StructureFactory::StructuresStatsTable_["Lair"];
    EXPECT_EQ(lairStats[0]->upgradeCost_, 15000);
    EXPECT_EQ(lairStats[1]->upgradeCost_, 25000);
    EXPECT_EQ(lairStats[2]->upgradeCost_, 40000);
    EXPECT_EQ(lairStats[3]->upgradeCost_, 60000);

}


TEST(StructureFactoryTests, releaseStructure){
    EXPECT_NO_THROW(StructureFactory::releaseStructure("Castle", 1));
    auto castle1 = StructureFactory::releaseStructure("Castle", 1);
    EXPECT_EQ(castle1->getUpgradeCost(), 5000);
    auto newCastle = std::static_pointer_cast<Castle>(castle1);
    EXPECT_EQ(newCastle->getProfit(), 20);

    auto wall1 = StructureFactory::releaseStructure("Wall", 2);
    EXPECT_NO_THROW(StructureFactory::releaseStructure("Wall", 2));
    EXPECT_EQ(wall1->getUpgradeCost(), 500);
    auto newWall = std::static_pointer_cast<Wall>(wall1);
    EXPECT_EQ(newWall->getMaxHP(), 700);

    EXPECT_NO_THROW(StructureFactory::releaseStructure("Lair", 3));
    auto lair = StructureFactory::releaseStructure("Lair", 3);
    
    EXPECT_NO_THROW(StructureFactory::releaseStructure("Tower", 4));
    auto tower = StructureFactory::releaseStructure("Tower", 4);
    EXPECT_EQ(tower->getUpgradeCost(), 1100);
    auto newTower = std::static_pointer_cast<Tower>(tower);
    EXPECT_EQ(newTower->getRange(), 5);
    EXPECT_EQ(newTower->getDamage(), 110);
    EXPECT_EQ(newTower->getFireRate(), 2);
}