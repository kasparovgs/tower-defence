#include "tower.h"
#include "structureFactory.h"
#include <stdexcept>
#include <sstream>
#include <fstream>
#include <cmath>

std::size_t Tower::dealDamage() {
    return damage_;
}


void Tower::levelUp() {
    if (StructureFactory::StructuresStatsTable_["Tower"].size() < getLevel() + 1){
        throw std::logic_error("The structure has already reached its maximum level.");
    }
    setLevel(getLevel() + 1);
    setUpgradeCost(StructureFactory::StructuresStatsTable_["Tower"][getLevel()-1]->upgradeCost_);
    auto stats = static_pointer_cast<TowerStats>(StructureFactory::StructuresStatsTable_["Tower"][getLevel()-1]);
    range_ = stats->range_;
    damage_ = stats->damage_;
    fireRate_ = stats->fireRate_;
}

void Tower::makeMove() {
    Matrix matrix = getLandscape()->getFieldGrid();
    std::size_t towerX = getPosition().first;
    std::size_t towerY = getPosition().second;

    std::size_t madeAttacks = 0;
    for (int i = -range_; i <= static_cast<int>(range_) && madeAttacks < fireRate_; i++) {
        for (int j = -range_; j <= static_cast<int>(range_) && madeAttacks < fireRate_; j++) {
            int newX = towerX + i;
            int newY = towerY + j;

            if (newX >= 0 && newX < static_cast<int>(getLandscape()->getMapSize()) && newY >= 0 && newY < static_cast<int>(getLandscape()->getMapSize())) {
                if (std::sqrt(i * i + j * j) <= range_ && matrix[newX][newY].getEnemy() != nullptr) {
                    matrix[newX][newY].getEnemy() -> takeDamage(dealDamage());
                    madeAttacks++;
                }
            }
        }
    }
}


std::shared_ptr<StructureStats> Tower::getStats() const {
    return std::make_shared<TowerStats>(getUpgradeCost(), getRange(), getDamage(), getFireRate());
}