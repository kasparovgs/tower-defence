#include <gtest/gtest.h>
#include "game.h"
#include "lair.h"
#include "wall.h"
#include "castle.h"
#include "tower.h"
TEST(GameTests, ConstructorTest){
    EXPECT_NO_THROW(Game());
}

TEST(GameTest, landscapeMethods){
    Game game{};
    game.initGame("tests/configs/");
    auto str1 = game.getLandscape()->getFieldGrid()[0][0].getStructure();
    auto str2 = game.getLandscape()->getFieldGrid()[7][3].getStructure();
    auto str3 = game.getLandscape()->getFieldGrid()[5][3].getStructure();
    auto str4 = game.getLandscape()->getFieldGrid()[5][4].getStructure();
    auto str5 = game.getLandscape()->getFieldGrid()[4][9].getStructure();
    auto str6 = game.getLandscape()->getFieldGrid()[6][7].getStructure();
    EXPECT_EQ(typeid(*(str1)), typeid(Lair));
    EXPECT_EQ(typeid(*(str2)), typeid(Castle));
    EXPECT_EQ(typeid(*(str3)), typeid(Wall));
    EXPECT_EQ(typeid(*(str4)), typeid(Wall));
    EXPECT_EQ(typeid(*(str5)), typeid(Tower));
    EXPECT_EQ(typeid(*(str6)), typeid(Tower));
}


TEST(GameTest, initGame){
    Game game{};
    game.initGame("tests/configs/");
    EXPECT_EQ(typeid(game.getLandscape()), typeid(game.getLandscape()->getStructureByPosition({4,9}) -> getLandscape()));
    EXPECT_EQ(game.getLandscape()->getMapSize(), game.getLandscape()->getStructureByPosition({4,9}) -> getLandscape()->getMapSize());

    // Проверка, что указатели на Landscape одинаковые из structures и enemy и из Game
    EXPECT_EQ((game.getLandscape().get()), (game.getLandscape()->getStructureByPosition({4,9}) ->getLandscape().get()));

    EXPECT_EQ(typeid(*(std::static_pointer_cast<Wall>(game.getLandscape()->getStructureByPosition({5,3})))), typeid(Wall));
    EXPECT_NE(game.getLandscape()->getStructureByPosition({5, 3}), nullptr);

    EXPECT_EQ(typeid(*(std::static_pointer_cast<Wall>(game.getLandscape()->getStructureByPosition({5,4})))), typeid(Wall));
    EXPECT_NE(game.getLandscape()->getStructureByPosition({5, 4}), nullptr);
}


TEST(GameTest, makeMove) {
    Game game{};
    game.initGame("tests/configs/");
    EXPECT_NO_THROW(game.makeMove());
    EXPECT_EQ(GlobalTime::getTime(), 1);
    for (std::size_t i = 0; i < 5; i++) {
        game.makeMove();
    }
}