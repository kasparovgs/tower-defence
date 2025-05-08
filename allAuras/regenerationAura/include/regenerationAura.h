#ifndef REGENERATIONAURA_H
#define REGENERATIONAURA_H

#include "aura.h"

class RegenerationAura: public Aura{
public:
    RegenerationAura() : Aura(AuraType::REGENERATION) {}
    static constexpr std::size_t REGENERATION_BOOST = 3;
    void applyEffect(const std::shared_ptr<Enemy>& enemy) const override;
    void removeEffect(const std::shared_ptr<Enemy>& enemy) const override;
};

#endif