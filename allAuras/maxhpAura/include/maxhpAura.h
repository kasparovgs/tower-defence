#ifndef MAXHP_H
#define MAXHP_H

#include "aura.h"

class MaxhpAura: public Aura{
public:
    MaxhpAura() : Aura(AuraType::MAXHP) {};
    static constexpr std::size_t MAXHP_BOOST = 100;
    void applyEffect(const std::shared_ptr<Enemy>& enemy) const override;
    void removeEffect(const std::shared_ptr<Enemy>& enemy) const override;
};

#endif