#ifndef HEAVYINFANTRY_H
#define HEAVYINFANTRY_H

#include "enemy.h"
#include "dealDamage.h"

struct HeavyInfantryStats: public EnemyStats{
    std::size_t damage_ = 0;
    std::size_t range_ = 0;

    HeavyInfantryStats(std::size_t maxHP,
                       std::size_t regenerationRate,
                       std::size_t speed,
                       std::size_t damage,
                       std::size_t range) :
                       EnemyStats(maxHP, regenerationRate, speed),
                       damage_(damage),
                       range_(range) {}

    HeavyInfantryStats(const HeavyInfantryStats& other) :
                  EnemyStats(other.maxHP_, other.regenerationRate_, other.speed_),
                  damage_(other.damage_),
                  range_(other.range_) {}
};



class HeavyInfantry: public Enemy, public DealDamage{
private:
    std::shared_ptr<Structure> findTargetInRange();
    std::size_t damage_ = 0;
    std::size_t range_ = 0;
public:
    ~HeavyInfantry() override = default;
    HeavyInfantry() = default;
    HeavyInfantry(std::string name, 
                  std::size_t maxHP,
                  std::size_t currentHP, 
                  std::size_t regenerationRate, 
                  std::pair<int, int> position, 
                  std::size_t speed, 
                  std::size_t damage,
                  std::size_t range) : 
                  Enemy(name,
                  maxHP,
                  currentHP,
                  regenerationRate,
                  position,
                  speed),
                  damage_(damage),
                  range_(range) {}

    HeavyInfantry(std::shared_ptr<HeavyInfantryStats> stats):
            Enemy(stats->maxHP_,
                  stats->regenerationRate_,
                  stats->speed_),
            damage_(stats->damage_),
            range_(stats->range_) {}

    void setDamage(std::size_t damage) { damage_ = damage; }
    void setRange(std::size_t range) { range_ = range; }
    [[nodiscard]] std::size_t getDamage() const { return damage_; }
    [[nodiscard]] std::size_t getRange() const { return range_; }
    [[nodiscard]] std::shared_ptr<EnemyStats> getStats() const override;
    void makeMove() override;
    void findPath() override;
    std::size_t dealDamage() override;
    void takeDamage(std::size_t damage) override;
};


#endif