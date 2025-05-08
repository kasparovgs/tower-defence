#ifndef LAIR_H
#define LAIR_H

#include <memory>
#include <sstream>
#include <unordered_map>
#include <queue>
#include <functional>
#include "structure.h"
#include "aviation.h"
#include "lightInfantry.h"
#include "heavyInfantry.h"
#include "hero.h"


struct LairStats: public StructureStats {
    LairStats(std::size_t upgradeCost) : StructureStats(upgradeCost) {}
};


struct EnemyRelease{
    std::string type;
    std::size_t time;
    std::size_t interval;
    std::size_t level;

    bool operator>(const EnemyRelease& other) const{
        return time > other.time;
    }
};


class Lair: public Structure{
private:
    static std::priority_queue<EnemyRelease, std::vector<EnemyRelease>, std::greater<>> ReleaseQueue_;
    static std::unordered_map<std::string, std::vector<std::shared_ptr<EnemyStats>>> EnemiesStatsTable_;

    static std::unordered_map<std::string, std::function<std::shared_ptr<Enemy>(std::shared_ptr<EnemyStats> stats)>> createEnemyByName;
    static std::unordered_map<std::string, std::function<std::shared_ptr<EnemyStats>(std::stringstream& ss)>> createEnemyStatsByName;
public:
    ~Lair() override = default;
    Lair() = default;
    Lair(std::shared_ptr<StructureStats> stats) : Structure(stats->upgradeCost_) {}

    explicit Lair(const std::string& directory);
    std::shared_ptr<Enemy> releaseEnemyOnTime(std::size_t time);
    std::shared_ptr<Enemy> releaseEnemy(const std::string& name, std::size_t level);

    static std::priority_queue<EnemyRelease, std::vector<EnemyRelease>, std::greater<>>& getReleaseQueue(){ return ReleaseQueue_; }
    static std::unordered_map<std::string, std::vector<std::shared_ptr<EnemyStats>>>& getEnemiesStatsTable(){ return EnemiesStatsTable_; }
    
    static void loadReleaseQueueFromConfig(const std::string& filename);
    static void loadStatsFromConfig(const std::string& filename);

    static void clearReleaseQueue();

    [[nodiscard]] std::shared_ptr<StructureStats> getStats() const override;

    void levelUp() override;
    void makeMove() override;

};

#endif