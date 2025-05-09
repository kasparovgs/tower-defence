#include "regenerationAura.h"


void RegenerationAura::applyEffect(const std::shared_ptr<Enemy>& enemy) const{
    enemy->setRegenerationRate(enemy->getRegenerationRate() + REGENERATION_BOOST);
}


void RegenerationAura::removeEffect(const std::shared_ptr<Enemy>& enemy) const{
    enemy->setRegenerationRate(enemy->getRegenerationRate() - REGENERATION_BOOST);
}