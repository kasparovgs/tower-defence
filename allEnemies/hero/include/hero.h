#ifndef HERO_H
#define HERO_H

#include <vector>
#include <unordered_map>
#include <functional>
#include <memory>
#include <cmath>
#include "aura.h"

#include "enemy.h"
#include "lightInfantry.h"
#include "heavyInfantry.h"
#include "aviation.h"
#include "speedAura.h"
#include "regenerationAura.h"
#include "maxhpAura.h"

template<typename T>
concept DerivedFromEnemyStats = std::is_base_of_v<EnemyStats, T>;

template<typename T>
concept IsAviationStats = std::is_same_v<T, AviationStats>;

template<typename T>
concept IsLightInfantryStats = std::is_same_v<T, LightInfantryStats>;

template<typename T>
concept DerivedFromEnemy = std::is_base_of_v<Enemy, T>;

template<typename T>
concept IsAviation = std::is_same_v<T, Aviation>;

template<typename T>
concept IsLightInfantry = std::is_same_v<T, LightInfantry>;



template <DerivedFromEnemyStats V>
struct HeroStats: public V {
     std::size_t auraRadius_ = 0;
     std::vector<std::string> auras_;

     HeroStats(std::size_t maxHP,
               std::size_t regenerationRate,
               std::size_t speed,
               std::size_t ammo,
               std::size_t auraRadius,
               std::vector<std::string> auras) requires IsAviationStats<V> :
               V(maxHP, regenerationRate, speed, ammo),
               auraRadius_(auraRadius),
               auras_(auras) {}
     
     HeroStats(std::size_t maxHP,
               std::size_t regenerationRate,
               std::size_t speed,
               std::size_t damage,
               std::size_t range,
               std::size_t auraRadius,
               std::vector<std::string> auras) :
               V(maxHP, regenerationRate, speed, damage, range),
               auraRadius_(auraRadius),
               auras_(auras) {}


     HeroStats(std::size_t maxHP,
               std::size_t regenerationRate,
               std::size_t speed,
               std::size_t missChance,
               std::size_t auraRadius,
               std::vector<std::string> auras) requires IsLightInfantryStats<V>:
               V(maxHP, regenerationRate, speed, missChance),
               auraRadius_(auraRadius),
               auras_(auras) {}

     HeroStats(const V& stats,
               std::size_t auraRadius,
               std::vector<std::string> auras) :
               V(stats),
               auraRadius_(auraRadius),
               auras_(auras) {}
};


template<DerivedFromEnemy T, DerivedFromEnemyStats W = EnemyStats>
class Hero: public T {
private:
    std::vector<std::shared_ptr<Aura>> auras_;
    std::size_t auraRadius_ = 0;
public:
     ~Hero() override {
        std::for_each(auras_.begin(), auras_.end(), [&](const std::shared_ptr<Aura>& aura) {
            std::for_each(aura->getAffectOn().begin(), aura->getAffectOn().end(), [&](const std::weak_ptr<Enemy>& weakEnemy) {
                if (auto enemy = weakEnemy.lock()) {
                    aura->removeEffect(enemy);
                }
            });
        });
     }
     Hero() = default;
     Hero(std::string name, 
         std::size_t maxHP,
         std::size_t currentHP,
         std::size_t regenerationRate,
         std::pair<int, int> position,
         std::size_t speed,
         std::size_t missChance,
         std::size_t auraRadius) requires IsLightInfantry<T>:
         T(
         name,
         maxHP,
         currentHP,
         regenerationRate,
         position,
         speed,
         missChance
         ),
         auraRadius_(auraRadius) {}


     Hero(std::shared_ptr<HeroStats<W>> stats):
          T(std::dynamic_pointer_cast<W>(stats)),
          auraRadius_(stats->auraRadius_) {
               for (const auto& auraName: stats->auras_) {
                    auto aura = createAuraByName(auraName);
                    if (aura != nullptr) {
                         auras_.emplace_back(aura);
                    }
               }
          }
     


     Hero(std::string name, 
         std::size_t maxHP, std::size_t currentHP, 
         std::size_t regenerationRate, 
         std::pair<int, int> position, 
         std::size_t speed,
         std::size_t damage,
         std::size_t range,
         std::size_t auraRadius) requires IsAviation<T>:
         T(
         name,
         maxHP,
         currentHP,
         regenerationRate,
         position,
         speed,
         damage,
         range
         ),
         auraRadius_(auraRadius) {}
         
     Hero(std::string name, 
         std::size_t maxHP,
         std::size_t currentHP, 
         std::size_t regenerationRate, 
         std::pair<int, int> position, 
         std::size_t speed,
         std::size_t ammo,
         std::size_t auraRadius) :
         T(
         name,
         maxHP,
         currentHP,
         regenerationRate,
         position,
         speed,
         ammo
         ),
         auraRadius_(auraRadius) {}


    std::shared_ptr<Aura> createAuraByName(const std::string& auraName) {
        static const std::unordered_map<std::string, std::function<std::shared_ptr<Aura>()>> auraFactory = {
            {"MaxhpAura", []() { return std::make_shared<MaxhpAura>(); }},
            {"RegenerationAura", []() { return std::make_shared<RegenerationAura>(); }},
            {"SpeedAura", []() { return std::make_shared<SpeedAura>(); }},
            {"null", []() { return nullptr; }}
        };

        auto aura = auraFactory.find(auraName);
        if (aura != auraFactory.end()) {
            return aura->second();
        }
        else {
            throw std::invalid_argument("Unknown aura name: " + auraName);
        }
    }

    [[nodiscard]] std::size_t getAuraRadius() const { return auraRadius_; }
    [[nodiscard]] std::vector<std::shared_ptr<Aura>> getAuras() const { return auras_; }
    void findPath() { T::findPath(); }

    void removeEnemiesOutOfRange() {
        std::for_each(auras_.begin(), auras_.end(), [&](const std::shared_ptr<Aura>& aura) {
            std::for_each(aura->getAffectOn().begin(), aura->getAffectOn().end(), [&](const std::weak_ptr<Enemy>& weakEnemy) {
                if (auto enemy = weakEnemy.lock()) {  // Проверяем, жив ли враг
                    auto [heroX, heroY] = this->getPosition();
                    auto [enemyX, enemyY] = enemy->getPosition();
                    auto distanceSquared = static_cast<std::size_t>((enemyX - heroX) * (enemyX - heroX) + (enemyY - heroY) * (enemyY - heroY));
                    if (distanceSquared > auraRadius_ * auraRadius_) {
                        aura->removeEnemy(enemy);
                    }
                }
            });
        });
    }

    void makeMove() {
        this->removeEnemiesOutOfRange();
        Matrix matrix = this->getLandscape()->getFieldGrid();
        auto [posX, posY] = this->getPosition();
        for (int i = -auraRadius_; i <= static_cast<int>(auraRadius_); i++) {
            for (int j = -auraRadius_; j <= static_cast<int>(auraRadius_); j++) {
                int newX = posX + i;
                int newY = posY + j;

                if (newX >= 0 && newX < static_cast<int>(this->getLandscape()->getMapSize()) 
                    && newY >= 0 && newY < static_cast<int>(this->getLandscape()->getMapSize())) {
                        if (std::sqrt(i * i + j* j) <= auraRadius_ && matrix[newX][newY].getEnemy() != nullptr) {
                            auto enemy = matrix[newX][newY].getEnemy();
                            std::for_each(auras_.begin(), auras_.end(), [&](const std::shared_ptr<Aura>& aura) {
                                aura->addEnemy(enemy);
                            });
                        }
                }
            }
        }
        T::makeMove();
    }
    void takeDamage(std::size_t damage) { T::takeDamage(damage); }
    std::vector<std::shared_ptr<Aura>> getAuras() { return auras_; }
    [[nodiscard]] std::shared_ptr<EnemyStats> getStats() const override {
        auto enemyStats = T::getStats();
        auto basedStats = std::static_pointer_cast<W>(enemyStats);
        std::vector<std::string> empty;
        return std::make_shared<HeroStats<W>>(*basedStats, auraRadius_, empty);
    };
};


#endif