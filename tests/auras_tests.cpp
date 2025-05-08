#include <gtest/gtest.h>
#include "aura.h"
#include "maxhpAura.h"
#include "regenerationAura.h"
#include "speedAura.h"
#include "aviation.h"
#include "hero.h"


TEST(AurasTests, addEnemy) {
    auto hpAura = std::make_shared<MaxhpAura>();
    auto enemy = std::make_shared<Aviation>();
    auto prevHP = enemy->getMaxHP();
    EXPECT_NO_THROW(hpAura->addEnemy(enemy));
    hpAura->addEnemy(enemy);
    EXPECT_EQ(enemy->getMaxHP(), prevHP + hpAura->MAXHP_BOOST);
    EXPECT_NO_THROW(hpAura->addEnemy(enemy));
}