#ifndef SPEEDAURA_H
#define SPEEDAURA_H

#include "aura.h"

class SpeedAura: public Aura{
public:
    SpeedAura() : Aura(AuraType::SPEED_BOOST) {};
    static constexpr std::size_t SPEED_BOOST = 2;
    void applyEffect(const std::shared_ptr<Enemy>& enemy) const override;
    void removeEffect(const std::shared_ptr<Enemy>& enemy) const override;
};

#endif