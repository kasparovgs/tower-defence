#ifndef WALL_H
#define WALL_H

#include "structure.h"
#include "IDamageable.h"
#include <memory>
#include <atomic>

struct WallStats: public StructureStats{
    std::size_t maxHP_;
    std::size_t currentHP_;

    WallStats(std::size_t upgradeCost,
               std::size_t maxHP) :
               StructureStats(upgradeCost),
               maxHP_(maxHP),
               currentHP_(maxHP) {}
    
    WallStats(std::size_t upgradeCost,
               std::size_t maxHP,
               std::size_t currentHP) :
               StructureStats(upgradeCost),
               maxHP_(maxHP),
               currentHP_(currentHP) {}
};

class Wall: public Structure, public IDamageable{
private:
    std::size_t maxHP_ = 0;
    std::atomic<std::size_t> currentHP_ = 0;
public:
    ~Wall() override = default;
    Wall() = default;
    Wall(std::size_t maxHP, std::size_t currentHP) : maxHP_(maxHP), currentHP_(currentHP) {}

    Wall(std::shared_ptr<WallStats> stats) :
         Structure(stats->upgradeCost_),
         maxHP_(stats->maxHP_),
         currentHP_(stats->maxHP_) {}

    void levelUp() override;
    void makeMove() override;

    void setMaxHP(std::size_t maxHP) { maxHP_ = maxHP; }
    void setCurrentHP(std::size_t currentHP) { currentHP_ = currentHP; }
    void takeDamage(std::size_t damage) override;

    [[nodiscard]] std::size_t getMaxHP() const { return maxHP_; }
    [[nodiscard]] std::atomic<std::size_t>& getCurrentHP() { return currentHP_; }
    [[nodiscard]] std::size_t getCurrentHPValue() const { return currentHP_.load(); }
    [[nodiscard]] std::shared_ptr<StructureStats> getStats() const override;
};


#endif