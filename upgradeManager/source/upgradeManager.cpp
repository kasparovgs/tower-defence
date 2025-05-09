#include "upgradeManager.h"
#include "globalGold.h"
#include "structure.h"

void UpgradeManager::levelUp(std::shared_ptr<Structure> structure) {
    auto gold = GlobalGold::getGold();
    auto upgradeCost = structure->getUpgradeCost();
    if (gold < upgradeCost) {
        throw std::logic_error("Insufficient funds");
    }
    structure->levelUp();
    GlobalGold::setGold(gold - upgradeCost);
}
