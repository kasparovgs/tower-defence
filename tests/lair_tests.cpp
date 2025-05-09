#include <gtest/gtest.h>
#include "lair.h"
#include "game.h"

TEST(LairTests, loadStatsFromConfig){
    EXPECT_NO_THROW(Lair::loadStatsFromConfig("tests/configs/enemies_config.csv"));
    Lair::loadStatsFromConfig("tests/configs/enemies_config.csv");

    EXPECT_EQ(Lair::getEnemiesStatsTable()["Aviation"][0]->maxHP_, 200);
    EXPECT_EQ(Lair::getEnemiesStatsTable()["Aviation"][3]->maxHP_, 350);
    EXPECT_EQ(Lair::getEnemiesStatsTable()["LightInfantry"][0]->maxHP_, 50);
    EXPECT_EQ(Lair::getEnemiesStatsTable()["LightInfantry"][3]->maxHP_, 125);
    EXPECT_EQ(Lair::getEnemiesStatsTable()["HeavyInfantry"][0]->maxHP_, 400);
    EXPECT_EQ(Lair::getEnemiesStatsTable()["HeavyInfantry"][3]->maxHP_, 700);
    EXPECT_EQ(Lair::getEnemiesStatsTable()["HeroAviation"][0]->maxHP_, 200);

    auto stats1 = Lair::getEnemiesStatsTable()["HeroAviation"][0];
    auto heroAviationStats1 = std::static_pointer_cast<HeroStats<AviationStats>>(stats1);
    EXPECT_EQ(heroAviationStats1->auraRadius_, 2);

    EXPECT_EQ(Lair::getEnemiesStatsTable()["HeroLightInfantry"][0]->maxHP_, 50);

    auto stats2 = Lair::getEnemiesStatsTable()["HeroLightInfantry"][3];
    auto heroAviationStats2 = std::static_pointer_cast<HeroStats<LightInfantryStats>>(stats2);
    EXPECT_EQ(heroAviationStats2->auraRadius_, 5);

    auto stats3 = Lair::getEnemiesStatsTable()["HeroHeavyInfantry"][3];
    auto heroAviationStats3 = std::static_pointer_cast<HeroStats<HeavyInfantryStats>>(stats3);
    EXPECT_EQ(heroAviationStats3->auraRadius_, 5);
    std::vector<std::string> expectedAuras = {"MaxhpAura", "RegenerationAura", "SpeedAura"};
    EXPECT_EQ(heroAviationStats3->auras_, expectedAuras);


    auto stats4 = Lair::getEnemiesStatsTable()["HeroLightInfantry"][3];
    auto heroLightStats4 = std::static_pointer_cast<HeroStats<LightInfantryStats>>(stats4);
    std::vector<std::string> expectedAuras2 = {"null", "RegenerationAura", "SpeedAura"};
    EXPECT_EQ(heroLightStats4->auras_, expectedAuras2);

    EXPECT_EQ(Lair::getEnemiesStatsTable()["HeroHeavyInfantry"][0]->maxHP_, 400);

    EXPECT_THROW(Lair::loadStatsFromConfig("/home/gkasp/oop2024/3/tests/enemies_config.csv"), std::runtime_error);

}

TEST(LairTests, loadReleaseQueueFromConfig){
    EXPECT_NO_THROW(Lair::loadReleaseQueueFromConfig("tests/configs/releaseEnemies_config.csv"));
    Lair::loadReleaseQueueFromConfig("tests/configs/releaseEnemies_config.csv");
    EXPECT_EQ(Lair::getReleaseQueue().top().type, "LightInfantry");
    EXPECT_EQ(Lair::getReleaseQueue().top().time, 2);
    EXPECT_EQ(Lair::getReleaseQueue().top().interval, 2);
    EXPECT_EQ(Lair::getReleaseQueue().top().level, 1);

    EXPECT_THROW(Lair::loadReleaseQueueFromConfig("/home/gkasp/oop2024/3/tests/enemies_config.csv"), std::runtime_error);

}


TEST(LairTests, releaseEnemy){
    Lair lair{};
    EXPECT_NO_THROW(lair.releaseEnemy("Aviation", 2));
    EXPECT_NO_THROW(lair.releaseEnemy("LightInfantry", 1));
    EXPECT_NO_THROW(lair.releaseEnemy("HeavyInfantry", 2));
    EXPECT_NO_THROW(lair.releaseEnemy("HeroAviation", 3));
    EXPECT_NO_THROW(lair.releaseEnemy("HeroLightInfantry", 1));
    EXPECT_NO_THROW(lair.releaseEnemy("HeroHeavyInfantry", 3));

    auto enemy1 = lair.releaseEnemy("Aviation", 2);
    auto enemy2 = lair.releaseEnemy("LightInfantry", 1);
    auto enemy3 = lair.releaseEnemy("HeavyInfantry", 2);
    auto enemy4 = lair.releaseEnemy("HeroAviation", 3);
    auto enemy5 = lair.releaseEnemy("HeroLightInfantry", 1);
    auto enemy6 = lair.releaseEnemy("HeroHeavyInfantry", 3);
    auto enemy7 = lair.releaseEnemy("HeroHeavyInfantry", 4);
    EXPECT_EQ(enemy1->getSpeed(), Lair::getEnemiesStatsTable()["Aviation"][2]->speed_);

    EXPECT_EQ(std::dynamic_pointer_cast<LightInfantry>(enemy2)->getCurrentHP(),
              std::static_pointer_cast<LightInfantryStats>(Lair::getEnemiesStatsTable()["LightInfantry"][0])->maxHP_);


    EXPECT_EQ(std::dynamic_pointer_cast<LightInfantry>(enemy2)->getMissChance(),
              std::static_pointer_cast<LightInfantryStats>(Lair::getEnemiesStatsTable()["LightInfantry"][0])->missChance_);

    EXPECT_EQ(std::dynamic_pointer_cast<HeavyInfantry>(enemy3)->getDamage(),
              std::static_pointer_cast<HeavyInfantryStats>(Lair::getEnemiesStatsTable()["HeavyInfantry"][1])->damage_);

    EXPECT_EQ(std::static_pointer_cast<Hero<Aviation>>(enemy4)->getAmmo(),
              std::static_pointer_cast<HeroStats<AviationStats>>(Lair::getEnemiesStatsTable()["HeroAviation"][2])->ammo_);
    EXPECT_EQ(std::static_pointer_cast<Hero<Aviation>>(enemy4)->getAuraRadius(),
              std::static_pointer_cast<HeroStats<AviationStats>>(Lair::getEnemiesStatsTable()["HeroAviation"][2])->auraRadius_);

    EXPECT_EQ(std::static_pointer_cast<Hero<LightInfantry>>(enemy5)->getMissChance(),
              std::static_pointer_cast<HeroStats<LightInfantryStats>>(Lair::getEnemiesStatsTable()["HeroLightInfantry"][0])->missChance_);
    EXPECT_EQ(std::static_pointer_cast<Hero<LightInfantry>>(enemy5)->getAuraRadius(),
              std::static_pointer_cast<HeroStats<LightInfantryStats>>(Lair::getEnemiesStatsTable()["HeroLightInfantry"][0])->auraRadius_);

    EXPECT_EQ(std::static_pointer_cast<Hero<HeavyInfantry>>(enemy6)->getRange(),
              std::static_pointer_cast<HeroStats<HeavyInfantryStats>>(Lair::getEnemiesStatsTable()["HeroHeavyInfantry"][2])->range_);
    EXPECT_EQ(std::static_pointer_cast<Hero<HeavyInfantry>>(enemy6)->getAuraRadius(),
              std::static_pointer_cast<HeroStats<HeavyInfantryStats>>(Lair::getEnemiesStatsTable()["HeroHeavyInfantry"][2])->auraRadius_);

    EXPECT_EQ((std::static_pointer_cast<Hero<HeavyInfantry>>(enemy7)->getAuras()[0]) -> getAuraType(),
              AuraType::MAXHP);

    EXPECT_EQ((std::static_pointer_cast<Hero<HeavyInfantry>>(enemy7)->getAuras()[1]) -> getAuraType(),
              AuraType::REGENERATION);

    EXPECT_EQ((std::static_pointer_cast<Hero<HeavyInfantry>>(enemy7)->getAuras()[2]) -> getAuraType(),
              AuraType::SPEED_BOOST);

    auto enemyTest = lair.releaseEnemy("HeroAviation", 4);
    std::vector<AuraType> check = {AuraType::MAXHP, AuraType::SPEED_BOOST};

    ASSERT_NE(enemyTest, nullptr);
    ASSERT_FALSE(std::static_pointer_cast<Hero<HeavyInfantry>>(enemy6)->getAuras().empty());
    EXPECT_EQ(std::static_pointer_cast<Hero<HeavyInfantry>>(enemy6)->getAuras().size(), 2);

    EXPECT_THROW(lair.releaseEnemy("HeroHeavyInfantry", 10), std::out_of_range);
    EXPECT_THROW(lair.releaseEnemy("NoType", 1), std::invalid_argument);

    Lair::clearReleaseQueue();
}


TEST(LairTests, releaseEnemyOnTime){
    Lair lair{};
    Lair::loadStatsFromConfig("tests/configs/enemies_config.csv");
    Lair::loadReleaseQueueFromConfig("tests/configs/releaseEnemies_config.csv");

    EXPECT_NO_THROW(lair.releaseEnemyOnTime(2));
    EXPECT_EQ(Lair::getReleaseQueue().top().type, "LightInfantry");
    EXPECT_EQ(Lair::getReleaseQueue().top().time, 4);
    EXPECT_EQ(lair.releaseEnemyOnTime(10), nullptr);
    lair.releaseEnemyOnTime(4);
    EXPECT_EQ(Lair::getReleaseQueue().top().time, 6);
}


TEST(LairTests, makeMove) {
    Game game{};
    game.initGame("tests/configs/");
    auto lairPos = game.getLandscape()->getLairPosition();
    auto lair = game.getLandscape()->getStructureByPosition(lairPos);
    EXPECT_NO_THROW(lair->makeMove());
    GlobalTime::setTime(2);
    lair->makeMove();
    EXPECT_EQ(typeid(*(game.getLandscape()->getEnemyByPosition(lairPos))), typeid(LightInfantry));
    EXPECT_NE(game.getLandscape()->getEnemyByPosition(lairPos), nullptr);
}