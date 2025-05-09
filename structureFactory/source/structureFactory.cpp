#include "structureFactory.h"
#include <fstream>
#include <filesystem>
#include <random>
#include <exception>

std::unordered_map<std::string, std::vector<std::shared_ptr<StructureStats>>> StructureFactory::StructuresStatsTable_;


std::string generate_name(std::size_t length){
    const std::string CHARACTERS = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> distribution(0, CHARACTERS.size() - 1);

    std::string random_string;

    for (std::size_t i = 0; i < length; ++i){
        random_string += CHARACTERS[distribution(generator)];
    }

    return random_string;
}


std::unordered_map<std::string, std::function<std::shared_ptr<Structure>(std::shared_ptr<StructureStats> stats)>> StructureFactory::createStructureByName = {
    {"Castle", [](std::shared_ptr<StructureStats> stats) {
        auto castleStats = std::static_pointer_cast<CastleStats>(stats);
        return std::make_shared<Castle>(castleStats); }},

    {"Tower", [](std::shared_ptr<StructureStats> stats) {
        auto towerStats = std::static_pointer_cast<TowerStats>(stats);
        return std::make_shared<Tower>(towerStats); }},

    {"Wall", [](std::shared_ptr<StructureStats> stats) {
        auto heavyInfantryStats = std::static_pointer_cast<WallStats>(stats);
        return std::make_shared<Wall>(heavyInfantryStats); }},

    {"Lair", [](std::shared_ptr<StructureStats> stats) {
        return std::make_shared<Lair>(stats); }}
};


std::unordered_map<std::string, std::function<std::shared_ptr<StructureStats>(std::stringstream& ss)>> StructureFactory::createStructureStatsByName = {
    {"Castle", [](std::stringstream& ss) {
        std::size_t upgradeCost, profit, maxHP, repairSpeed;
        char comma;
        ss >> upgradeCost >> comma >> profit >> comma >> maxHP >> comma >> repairSpeed;
        return std::make_shared<CastleStats>(upgradeCost, profit, maxHP, repairSpeed); }},

    {"Tower", [](std::stringstream& ss) {
        std::size_t upgradeCost, range, damage, fireRate;
        char comma;
        ss >> upgradeCost >> comma >> comma >> comma >> comma >> range >> comma >> damage >> comma >> fireRate;
        return std::make_shared<TowerStats>(upgradeCost, range, damage, fireRate); }},

    {"Wall", [](std::stringstream& ss) {
        std::size_t upgradeCost, maxHP;
        char comma;
        ss >> upgradeCost >> comma >> comma >> maxHP;
        return std::make_shared<WallStats>(upgradeCost, maxHP); }},

    {"Lair", [](std::stringstream& ss) {
        std::size_t upgradeCost;
        ss >> upgradeCost;
        return std::make_shared<StructureStats>(upgradeCost); }}
};


void StructureFactory::loadStatsFromConfig(const std::string& filePath){
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file " + filePath);
    }

    std::string line;

    std::getline(file, line);
    StructuresStatsTable_.clear();
    while (std::getline(file, line)){
        std::stringstream ss(line);
        std::string structureType;
        std::getline(ss, structureType, ',');
        
        if (createStructureStatsByName.find(structureType) != createStructureStatsByName.end()){
            auto StructureStats = createStructureStatsByName[structureType](ss);
            StructuresStatsTable_[structureType].emplace_back(StructureStats);
        }
        else{
            throw std::invalid_argument("Unknown type of structure.");
        }
    }
}


std::shared_ptr<Structure> StructureFactory::releaseStructure(const std::string& name, std::size_t level){ //DONE (не тестил)
    auto it = StructuresStatsTable_.find(name);
    if (it != StructuresStatsTable_.end()){
        auto statsVec = it->second;

        if (level > statsVec.size()){
            throw std::out_of_range("There is no such level.");
        }

        auto stats = statsVec[level-1];
        auto structure = createStructureByName[name](stats);

        structure->setLevel(level);
        structure->setName(generate_name(6));

        return structure;
    }
    else{
        throw std::invalid_argument("Structure not found.");
    }
}