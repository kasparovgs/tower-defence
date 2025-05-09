#ifndef CASTLE_H
#define CASTLE_H

#include <memory>
#include <exception>
#include <string>
#include <vector>
#include <iostream>
#include <atomic>
#include "structure.h"
#include "IDamageable.h"

class Enemy;

struct CastleStats: public StructureStats{
    std::size_t profit_;
    std::size_t maxHP_;
    std::size_t currentHP_;
    std::size_t repairSpeed_;

    CastleStats(std::size_t upgradeCost,
                std::size_t profit,
                std::size_t maxHP,
                std::size_t repairSpeed) :
                StructureStats(upgradeCost),
                profit_(profit),
                maxHP_(maxHP),
                currentHP_(maxHP),
                repairSpeed_(repairSpeed) {}
    
    CastleStats(std::size_t upgradeCost,
                std::size_t profit,
                std::size_t maxHP,
                std::size_t currentHP,
                std::size_t repairSpeed) :
                StructureStats(upgradeCost),
                profit_(profit),
                maxHP_(maxHP),
                currentHP_(currentHP),
                repairSpeed_(repairSpeed) {}
};


class Castle: public Structure, public IDamageable {
private:
    std::size_t maxHP_ = 0;
    std::atomic<std::size_t> currentHP_ = 0;
    std::size_t accumulatedGold_ = 0;
    std::size_t profit_ = 0;
    std::size_t repairSpeed_ = 0;
public:
    ~Castle() override = default;
    Castle() = default;
    Castle(std::shared_ptr<CastleStats> stats) :
           Structure(stats->upgradeCost_),
           maxHP_(stats->maxHP_),
           currentHP_(stats->maxHP_),
           profit_(stats->profit_),
           repairSpeed_(stats->repairSpeed_) {}

    void levelUp() override;

    void setMaxHP(std::size_t maxHP) { maxHP_ = maxHP; }
    void setCurrentHP(std::size_t currentHP) { currentHP_ = currentHP; }
    void makeMove() override;

    [[nodiscard]] std::size_t getMaxHP() const { return maxHP_; }
    [[nodiscard]] std::atomic<std::size_t>& getCurrentHP() { return currentHP_; }
    [[nodiscard]] std::size_t getCurrentHPValue() const { return currentHP_.load(); }
    [[nodiscard]] std::size_t getProfit() const { return profit_; }
    [[nodiscard]] std::size_t getRepairSpeed() const { return repairSpeed_; }
    [[nodiscard]] std::size_t getAccumulatedGold() const { return accumulatedGold_; }
    [[nodiscard]] std::size_t collectAccumulatedGold();
    [[nodiscard]] std::shared_ptr<StructureStats> getStats() const override;

    void takeDamage(std::size_t damage) override;
    static CastleStats getStats(std::size_t index);

};


#endif