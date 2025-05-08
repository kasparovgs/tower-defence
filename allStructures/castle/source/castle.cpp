#include "castle.h"
#include "structureFactory.h"
#include "GameOverException.h"

void Castle::levelUp() {
    if (StructureFactory::StructuresStatsTable_["Castle"].size() < getLevel() + 1){
        throw std::logic_error("The structure has already reached its maximum level.");
    }
    setLevel(getLevel() + 1);
    setUpgradeCost(StructureFactory::StructuresStatsTable_["Castle"][getLevel()-1]->upgradeCost_);
    auto stats = static_pointer_cast<CastleStats>(StructureFactory::StructuresStatsTable_["Castle"][getLevel()-1]);
    setMaxHP(stats->maxHP_);
    profit_ = stats->profit_;
    repairSpeed_ = stats->repairSpeed_;
}


void Castle::makeMove() {
    (currentHP_ + repairSpeed_ >= maxHP_) ? (currentHP_ = maxHP_) : (currentHP_ += repairSpeed_);
    accumulatedGold_ += profit_;
}


std::size_t Castle::collectAccumulatedGold() {
    std::size_t gold = accumulatedGold_;
    accumulatedGold_ = 0;
    return gold;
}


void Castle::takeDamage(std::size_t damage) {
    if (damage >= getCurrentHP()){
        throw GameOverException("The castle is destroyed, the game is over");
    }
    std::size_t hp = getCurrentHP().load();
    while (hp > 0 && !getCurrentHP().compare_exchange_weak(hp, (damage > hp) ? 0 : hp - damage)) {}
}


std::shared_ptr<StructureStats> Castle::getStats() const {
    return std::make_shared<CastleStats>(getUpgradeCost(),
                                         getProfit(),
                                         getMaxHP(),
                                         getCurrentHPValue(),
                                         getRepairSpeed());
}