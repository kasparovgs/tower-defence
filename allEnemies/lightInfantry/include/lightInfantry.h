#ifndef LIGHTINFANTRY_H
#define LIGHTINFANTRY_H

#include "enemy.h"


struct LightInfantryStats: public EnemyStats{
    std::size_t missChance_ = 0;

    LightInfantryStats(std::size_t maxHP,
                       std::size_t regenerationRate,
                       std::size_t speed,
                       std::size_t missChance) :
                       EnemyStats(maxHP, regenerationRate, speed),
                       missChance_(missChance) {}
    
    LightInfantryStats(const LightInfantryStats& other) :
                  EnemyStats(other.maxHP_, other.regenerationRate_, other.speed_),
                  missChance_(other.missChance_) {}
};


class LightInfantry: public Enemy{
private:
    std::size_t missChance_ = 0;
public:
    LightInfantry() = default;
    ~LightInfantry() override = default;
    LightInfantry(std::string name,
                  std::size_t maxHP,
                  std::size_t currentHP,
                  std::size_t regenerationRate,
                  std::pair<int, int> position,
                  std::size_t speed,
                  std::size_t missChance) :
                  Enemy(name,
                  maxHP,
                  currentHP,
                  regenerationRate,
                  position,
                  speed),
                  missChance_(missChance) {}
    LightInfantry(std::shared_ptr<LightInfantryStats> stats):
            Enemy(stats->maxHP_,
                  stats->regenerationRate_,
                  stats->speed_),
            missChance_(stats->missChance_) {}
    void setMissChance(std::size_t missChance) { missChance_ = missChance; }
    [[nodiscard]] std::size_t getMissChance() const { return missChance_; }
    [[nodiscard]] std::shared_ptr<EnemyStats> getStats() const override;
    void makeMove() override;

    void findPath() override;
    void takeDamage(std::size_t damage) override;
};


#endif