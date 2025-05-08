#include "landscape.h"
#include "lair.h"
#include "enemy.h"
#include "structureFactory.h"
#include "globalGold.h"
#include <fstream>
#include <execution>


void Landscape::makeMove() {
    std::for_each(std::execution::par, structures_.begin(), structures_.end(), [&](auto& structure) {
        if (!structure->getValidity()) {
            auto pos = structure->getPosition();
            setStructureByPosition(pos, nullptr);
        } else {
            structure->makeMove();
        }
    });

    structures_.erase(std::remove_if(structures_.begin(), structures_.end(),
        [](const auto& structure) { return !structure->getValidity(); }), structures_.end());

    std::for_each(std::execution::par, enemies_.begin(), enemies_.end(), [&](auto& enemy) {
        if (enemy->getCurrentHP() == 0 || enemy->getPosition() == castlePos_) {
            auto pos = enemy->getPosition();
            setEnemyByPosition(pos, nullptr);
        }
        else {
            std::pair<int, int> prevPos = enemy->getPosition();
            enemy->makeMove();
            fieldGrid_[prevPos.first][prevPos.second].setEnemy(nullptr);
            auto [newX, newY] = enemy->getPosition();
            fieldGrid_[newX][newY].setEnemy(enemy);
        }
    });

    enemies_.erase(std::remove_if(enemies_.begin(), enemies_.end(),
        [&](const auto& enemy) { return enemy->getCurrentHP() == 0 || enemy->getPosition() == castlePos_; }), enemies_.end());
}


std::shared_ptr<Structure> Landscape::getStructureByPosition(const std::pair<int, int>& position) const {
    if (position.first >= static_cast<int>(mapSize_) || position.first < 0 || position.second >= static_cast<int>(mapSize_) || position.second < 0){
        throw std::out_of_range("The coordinate is not on the map.");
    }
    return fieldGrid_[position.first][position.second].getStructure();
}


std::shared_ptr<Enemy> Landscape::getEnemyByPosition(const std::pair<int, int>& position) const {
    if (position.first >= static_cast<int>(mapSize_) || position.first < 0 || position.second >= static_cast<int>(mapSize_) || position.second < 0){
        throw std::out_of_range("The coordinate is not on the map.");
    }
    return fieldGrid_[position.first][position.second].getEnemy();
}


void Landscape::setCastlePosition(const std::pair<int, int>& position) {
    if (position.first >= static_cast<int>(mapSize_) || position.first < 0 || position.second >= static_cast<int>(mapSize_) || position.second < 0){
        throw std::out_of_range("The coordinate is not on the map.");
    }
    castlePos_ = position;
}


void Landscape::setLairPosition(const std::pair<int, int>& position) {
    if (position.first >= static_cast<int>(mapSize_) || position.first < 0 || position.second >= static_cast<int>(mapSize_) || position.second < 0){
        throw std::out_of_range("The coordinate is not on the map.");
    }
    lairPos_ = position;
}


void Landscape::addEnemy(std::shared_ptr<Enemy> enemy) {
    enemy->setLandscape(getSelf());
    enemy->setPosition(lairPos_);
    setEnemyByPosition(lairPos_, enemy);
    enemy->findPath();
    enemies_.push_back(enemy);
}


void Landscape::changeLandscapeFromCSV(const std::string& directory) {
    changeFieldFromCSV(directory);
    changeStructuresFromCSV(directory);
    
    changeEnemiesFromCSV(directory);
}


void Landscape::changeEnemiesFromCSV(const std::string& filePath) {
    std::string filenameStats = "enemies_config.csv";
    std::string fullPathStats = filePath;
    fullPathStats += filenameStats;

    std::string filenameRelease = "releaseEnemies_config.csv";
    std::string fullPathRelease = filePath;
    fullPathRelease += filenameRelease;
    Lair::loadStatsFromConfig(fullPathStats);
    Lair::loadReleaseQueueFromConfig(fullPathRelease);
}


void Landscape::changeFieldFromCSV(const std::string& directory) {
    std::string filename = "landscape_config.csv";
    std::string fullPath = directory;
    fullPath += filename;

    std::ifstream file(fullPath);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file " + fullPath);
    }
    std::string line;

    std::size_t size;
    
    std::getline(file, line);
    std::getline(file, line);
    std::istringstream lineStream(line);
    lineStream.ignore(3);
    lineStream >> size;
    setMapSize(size);
    fieldGrid_.resize(size, size);
    lineStream.clear();
    while (std::getline(file, line)) {
        std::istringstream lineStream(line);
        std::string fieldTypeStr;
        fieldType fType;
        int x, y;

        std::getline(lineStream, fieldTypeStr, ',');
        lineStream >> x;
        lineStream.ignore(1);
        lineStream >> y;
        if (fieldTypeStr == "Plain"){
            fType = fieldType::Plain;
        }
        else if (fieldTypeStr == "Mountain"){
            fType = fieldType::Mountain;
        }
        else if (fieldTypeStr == "Water"){
            fType = fieldType::Water;
        }
        else{
            throw std::runtime_error("Unknown field type: " + fieldTypeStr);
        }
        fieldGrid_[x][y].setFieldType(fType);
    }
}


void Landscape::changeStructuresFromCSV(const std::string& filePath) {
    std::string filename = "structuresStats_config.csv";
    std::string fullPath = filePath;
    fullPath += filename;

    StructureFactory::loadStatsFromConfig(fullPath);
    
    filename = "structuresPositions_config.csv";
    fullPath = filePath;
    fullPath += filename;

    std::ifstream file(fullPath);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file " + fullPath);
    }

    std::string line;

    std::getline(file, line);

    while (std::getline(file, line)) {
        std::istringstream lineStream(line);
        std::string structureType;
        std::size_t level;
        int x, y;

        std::getline(lineStream, structureType, ',');
        lineStream >> level;
        lineStream.ignore(1);
        lineStream >> x;
        lineStream.ignore(1);
        lineStream >> y;
        if (x < 0 || y < 0 || x >= static_cast<int>(mapSize_) || y >= static_cast<int>(mapSize_)) {
            throw std::invalid_argument("Incorrect position of the building.");
        }
        auto structure = StructureFactory::releaseStructure(structureType, level);
        structure->setPosition({x, y});
        structure->setLandscape(getSelf());
        setStructureByPosition({x, y}, structure);
        if (structureType == "Castle"){
            setCastlePosition({x, y});
            GlobalGold::setCastle(structure);
        }
        if (structureType == "Lair"){
            setLairPosition({x, y});
        }
        structures_.push_back(structure);
    }
}


void Landscape::setStructureByPosition(const std::pair<int, int>& position, const std::shared_ptr<Structure> structure){
    if (position.first >= static_cast<int>(mapSize_) || position.first < 0 || position.second >= static_cast<int>(mapSize_) || position.second < 0){
        throw std::out_of_range("The coordinate is not on the map.");
    }
    fieldGrid_[position.first][position.second].setStructure(structure);
}


void Landscape::setEnemyByPosition(const std::pair<int, int>& position, const std::shared_ptr<Enemy> enemy) {
    if (position.first >= static_cast<int>(mapSize_) || position.first < 0 || position.second >= static_cast<int>(mapSize_) || position.second < 0){
        throw std::out_of_range("The coordinate is not on the map.");
    }
    fieldGrid_[position.first][position.second].setEnemy(enemy);
}