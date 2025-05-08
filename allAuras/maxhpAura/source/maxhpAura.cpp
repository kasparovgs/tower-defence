#include "maxhpAura.h"


void MaxhpAura::applyEffect(const std::shared_ptr<Enemy>& enemy) const{
    enemy->setMaxHP(enemy->getMaxHP() + MAXHP_BOOST);
}


void MaxhpAura::removeEffect(const std::shared_ptr<Enemy>& enemy) const{
    enemy->setMaxHP(enemy->getMaxHP() - MAXHP_BOOST);
}