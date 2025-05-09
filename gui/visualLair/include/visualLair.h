#ifndef VISUALLAIR_H
#define VISUALLAIR_H


#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <typeindex>
#include <memory>
#include <typeinfo>
#include <functional>
#include "visualEnemy.h"
#include "aviation.h"
#include "lightInfantry.h"
#include "heavyInfantry.h"
#include "hero.h"

class VisualLair {
private:
    static std::unordered_map<std::type_index, std::function<std::shared_ptr<VisualEnemy>(const std::shared_ptr<Enemy>& enemy)>> releaseVisualEnemyTable_;
    
public:
    VisualLair() = delete;
    static std::shared_ptr<VisualEnemy> releaseVisualEnemy(const std::shared_ptr<Enemy>& enemy);
};


#endif