#include "heavyInfantry.h"
#include "wall.h"
#include "castle.h"

#include <algorithm>
#include <queue>
#include <unordered_map>
#include <cmath>

std::size_t HeavyInfantry::dealDamage(){
    return damage_;
}


static int heuristic(int x1, int y1, int x2, int y2){
    return std::abs(x1 - x2) + std::abs(y1 - y2);  // Манхэттенское расстояние для сетки
}


static bool isValid(int x, int y, int mapSize){
    return x >= 0 && x < mapSize && y >= 0 && y < mapSize;
}


static bool isWalkable(int x, int y, Matrix matr){
    auto structure = std::static_pointer_cast<Wall>(matr[x][y].getStructure());
    return matr[x][y].getFieldType() == fieldType::Plain && 
    (matr[x][y].getStructure() == nullptr || typeid(*structure) == typeid(Wall));
}


void HeavyInfantry::findPath(){
    Matrix matrix = getLandscape()->getFieldGrid();
    std::vector<std::pair<int, int>> newPath;
    
    int startX = getLandscape()->getLairPosition().first;
    int startY = getLandscape()->getLairPosition().second;
    int endX = getLandscape()->getCastlePosition().first;
    int endY = getLandscape()->getCastlePosition().second;
    int mapSize = getLandscape()->getMapSize();

    std::priority_queue<std::pair<int, std::pair<int, int>>, 
                        std::vector<std::pair<int, std::pair<int, int>>>, 
                        std::greater<std::pair<int, std::pair<int, int>>>> openSet;
    
    std::unordered_map<int, std::unordered_map<int, int>> gScore;
    gScore[startX][startY] = 0;

    std::unordered_map<int, std::unordered_map<int, std::pair<int, int>>> cameFrom;

    openSet.push({heuristic(startX, startY, endX, endY), {startX, startY}});

    const std::vector<std::pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    while (!openSet.empty()) {
        auto current = openSet.top();
        openSet.pop();
        int currentX = current.second.first;
        int currentY = current.second.second;

        if (currentX == endX && currentY == endY) {

            for (std::pair<int, int> pos = {endX, endY}; pos != std::make_pair(startX, startY); pos = cameFrom[pos.first][pos.second]) {
                newPath.push_back(pos);
            }
            newPath.push_back({startX, startY});
            std::reverse(newPath.begin(), newPath.end());
            setPath(newPath);
            return;
        }

        for (const auto& dir : directions) {
            int newX = currentX + dir.first;
            int newY = currentY + dir.second;

            if ((isValid(newX, newY, mapSize) && isWalkable(newX, newY, matrix) )|| 
                (newX == endX && newY == endY)) {
                int tentativeGScore = gScore[currentX][currentY] + 1;
                if (gScore.find(newX) == gScore.end() || gScore[newX].find(newY) == gScore[newX].end() || tentativeGScore < gScore[newX][newY]) {
                    cameFrom[newX][newY] = {currentX, currentY};
                    gScore[newX][newY] = tentativeGScore;
                    int h = heuristic(newX, newY, endX, endY);
                    openSet.push({tentativeGScore + h, {newX, newY}});
                }
            }
        }
    }

    throw std::logic_error("It's impossible to get to the castle.");
}


void HeavyInfantry::takeDamage(std::size_t damage){
    std::size_t hp = getCurrentHP().load();
    while (hp > 0 && !getCurrentHP().compare_exchange_weak(hp, (damage > hp) ? 0 : hp - damage)) {}
}

std::shared_ptr<Structure> HeavyInfantry::findTargetInRange() {
    auto path = getPath();
    auto [posX, posY] = getPosition();
    std::size_t currentStep = getCurrentStep();
    for (std::size_t i = currentStep; i < path.size(); i++) {
        auto [pathX, pathY] = path[i];
        auto distanceSquared = static_cast<std::size_t>((pathX - posX) * (pathX - posX) + (pathY - posY) * (pathY - posY));

        if (distanceSquared > range_ * range_) {
            break;
        }

        auto structure = getLandscape()->getStructureByPosition({pathX, pathY});
        if (structure != nullptr && typeid(*structure) == typeid(Wall)) {
            return structure;
        }
    }
    return nullptr;
}

void HeavyInfantry::makeMove(){
    setCurrentHP(getCurrentHP() + getRegenerationRate() > getMaxHP() ? getMaxHP() : getCurrentHP() + getRegenerationRate());
    std::size_t finalStep = getCurrentStep() + getSpeed();
    auto path = getPath();
    auto matr = getLandscape()->getFieldGrid();
    if (finalStep >= path.size()) {
        finalStep = path.size() - 1;
    }

    do {
        auto target = findTargetInRange();

        if (target != nullptr && target->getValidity()) {
            auto wall = std::static_pointer_cast<Wall>(target);
            wall->takeDamage(dealDamage());
            return;
        }

        setCurrentStep(getCurrentStep() + 1);
        setPosition({path[getCurrentStep()].first, path[getCurrentStep()].second});
    } while (getCurrentStep() < finalStep);

    setCurrentStep(finalStep);
    setPosition({path[getCurrentStep()].first, path[getCurrentStep()].second});

    if (getCurrentStep() + 1 == path.size()) {
        auto [posX, posY] = path[getCurrentStep()];
        auto structure = matr[posX][posY].getStructure();
        auto castle = std::static_pointer_cast<Castle>(structure);
        castle->takeDamage(dealDamageToCastle());
    }
}


std::shared_ptr<EnemyStats> HeavyInfantry::getStats() const {
    return std::make_shared<HeavyInfantryStats>(getMaxHP(),
                                                getRegenerationRate(),
                                                getSpeed(),
                                                getDamage(),
                                                getRange());
}