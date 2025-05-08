#include "wall.h"
#include "structureFactory.h"

void Wall::levelUp() {
    if (StructureFactory::StructuresStatsTable_["Wall"].size() < getLevel() + 1){
        throw std::logic_error("The structure has already reached its maximum level.");
    }
    setLevel(getLevel() + 1);
    setUpgradeCost(StructureFactory::StructuresStatsTable_["Wall"][getLevel()-1]->upgradeCost_);
    auto stats = static_pointer_cast<WallStats>(StructureFactory::StructuresStatsTable_["Wall"][getLevel()-1]);
    setMaxHP(stats->maxHP_);
}

void Wall::takeDamage(std::size_t damage) {
    std::size_t hp = getCurrentHP().load();
    while (hp > 0) {
        if (getCurrentHP().compare_exchange_weak(hp, (damage > hp) ? 0 : hp - damage)) {
            break;
        }
    }
    if (hp == 0) {
        is_valid_ = false;
    }
}


void Wall::makeMove() {}


std::shared_ptr<StructureStats> Wall::getStats() const {
    return std::make_shared<WallStats>(getUpgradeCost(), getMaxHP(), getCurrentHPValue());
}