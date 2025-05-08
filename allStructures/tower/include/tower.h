#ifndef TOWER_H
#define TOWER_H

#include <string>
#include <vector>
#include <memory>
#include "structure.h"
#include "dealDamage.h"

struct TowerStats: public StructureStats{
    std::size_t range_;
    std::size_t damage_;
    std::size_t fireRate_;

    TowerStats(std::size_t upgradeCost,
               std::size_t range,
               std::size_t damage,
               std::size_t fireRate) :
               StructureStats(upgradeCost),
               range_(range),
               damage_(damage),
               fireRate_(fireRate) {}
};


class Tower: public Structure, public DealDamage{
private:
    std::size_t range_;
    std::size_t damage_;
    std::size_t fireRate_;
public:
    ~Tower() override = default;
    Tower() = default;
    Tower(std::shared_ptr<TowerStats> stats) :
          Structure(stats->upgradeCost_),
          range_(stats->range_),
          damage_(stats->damage_),
          fireRate_(stats->fireRate_) {}

    [[nodiscard]] std::size_t getRange() const { return range_; }
    [[nodiscard]] std::size_t getDamage() const { return damage_; }
    [[nodiscard]] std::size_t getFireRate() const { return fireRate_; }
    [[nodiscard]] std::shared_ptr<StructureStats> getStats() const override;

    std::size_t dealDamage() override;
    void levelUp() override;
    void makeMove() override;
};


#endif