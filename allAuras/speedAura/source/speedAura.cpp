#include "speedAura.h"


void SpeedAura::applyEffect(const std::shared_ptr<Enemy>& enemy) const{
    enemy->setSpeed(enemy->getSpeed() + SPEED_BOOST);
}


void SpeedAura::removeEffect(const std::shared_ptr<Enemy>& enemy) const{
    enemy->setSpeed(enemy->getSpeed() - SPEED_BOOST);
}