#ifndef AVIATION_H
#define AVIATION_H

#include "enemy.h"
#include "dealDamage.h"


struct AviationStats: public EnemyStats{
    std::size_t ammo_ = 0;

    AviationStats(std::size_t maxHP,
                  std::size_t regenerationRate,
                  std::size_t speed,
                  std::size_t ammo) :
                  EnemyStats(maxHP, regenerationRate, speed),
                  ammo_(ammo) {}
    
    AviationStats(const AviationStats& other) :
                  EnemyStats(other.maxHP_, other.regenerationRate_, other.speed_),
                  ammo_(other.ammo_) {}
};


class Aviation: public Enemy, public DealDamage{
private:
    std::size_t ammo_ = 0;
public:
    ~Aviation() override = default;
    Aviation() = default;
    Aviation(std::string name,
             std::size_t maxHP,
             std::size_t currentHP,
             std::size_t regenerationRate,
             std::pair<int, int> position,
             std::size_t speed,
             std::size_t ammo) : 
             Enemy(
             name,
             maxHP,
             currentHP,
             regenerationRate,
             position,
             speed
             ),
             ammo_(ammo) {}
    Aviation(std::shared_ptr<AviationStats> stats):
            Enemy(stats->maxHP_,
                  stats->regenerationRate_,
                  stats->speed_),
            ammo_(stats->ammo_) {}

    void setAmmo(std::size_t ammo){ ammo_ = ammo; }
    [[nodiscard]] std::size_t getAmmo() const { return ammo_; }
    [[nodiscard]] std::shared_ptr<EnemyStats> getStats() const override;
    void makeMove() override;
    void findPath() override;
    void takeDamage(std::size_t damage) override;
    std::size_t dealDamage() override;
};


#endif