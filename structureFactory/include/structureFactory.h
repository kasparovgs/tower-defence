#ifndef STRUCTUREFACTORY_H
#define STRUCTUREFACTORY_H

#include <memory>
#include <unordered_map>
#include <functional>
#include "structure.h"
#include "tower.h"
#include "castle.h"
#include "wall.h"
#include "lair.h"

class StructureFactory{
public:
    StructureFactory() = delete;
    static std::unordered_map<std::string, std::function<std::shared_ptr<Structure>(std::shared_ptr<StructureStats> stats)>> createStructureByName;
    static void loadStatsFromConfig(const std::string& filename);
    
    static std::unordered_map<std::string, std::vector<std::shared_ptr<StructureStats>>> StructuresStatsTable_;
    
    static std::shared_ptr<Structure> releaseStructure(const std::string& name, std::size_t level);

    static std::unordered_map<std::string, std::function<std::shared_ptr<StructureStats>(std::stringstream& ss)>> createStructureStatsByName;
};


#endif