#ifndef AURA_H
#define AURA_H

#include <memory>
#include <vector>
#include <algorithm>

#include "enemy.h"

enum class AuraType{
    SPEED_BOOST,
    REGENERATION,
    MAXHP
};


class Aura{
private:
    std::vector<std::weak_ptr<Enemy>> affectOn_;
    AuraType auraType_;
public:
    virtual ~Aura() = default;
    Aura(AuraType aura) : auraType_(aura) {}

    [[nodiscard]] std::vector<std::weak_ptr<Enemy>>& getAffectOn() { return affectOn_; }

    void addEnemy(std::shared_ptr<Enemy> enemy) {
        for (const auto& weakEnemy : affectOn_) {
            if (auto sharedEnemy = weakEnemy.lock()) {
                if (sharedEnemy == enemy) {
                    return;
                }
            }
        }
        affectOn_.push_back(enemy);
        applyEffect(enemy);
    }

    void removeEnemy(const std::shared_ptr<Enemy>& enemy) {
        removeEffect(enemy);
        affectOn_.erase(
            std::remove_if(affectOn_.begin(), affectOn_.end(), 
                       [&enemy](const std::weak_ptr<Enemy>& wptr) {
                           if (auto sptr = wptr.lock()) {
                               return sptr == enemy;
                           }
                           return false;
                       }),
        affectOn_.end());
}

    virtual void applyEffect(const std::shared_ptr<Enemy>& enemy) const = 0;
    virtual void removeEffect(const std::shared_ptr<Enemy>& enemy) const = 0;

    [[nodiscard]] AuraType getAuraType() const { return auraType_; }
    void setAuraType(AuraType type) { auraType_ = type; }
};

#endif