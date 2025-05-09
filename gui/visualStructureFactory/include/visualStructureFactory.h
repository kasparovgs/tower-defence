#ifndef VISUALSTRUCTUREFACTORY_H
#define VISUALSTRUCTUREFACTORY_H

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <typeindex>
#include <memory>
#include <typeinfo>
#include <functional>
#include "visualStructure.h"
#include "wall.h"
#include "lair.h"
#include "castle.h"
#include "tower.h"

class VisualStructureFactory {
private:
    static std::unordered_map<std::type_index, 
                              std::function<std::shared_ptr<VisualStructure>(const std::shared_ptr<Structure>& structure)>> releaseVisualStructureTable_;

public:
    VisualStructureFactory() = delete;
    static std::shared_ptr<VisualStructure> releaseVisualStructure(const std::shared_ptr<Structure>& structure);
};

#endif