#include "aviation.h"
//#include "landscape.h"
#include <climits>
#include <algorithm>
#include <queue>
#include <unordered_map>
#include "wall.h"
#include "castle.h"

std::size_t Aviation::dealDamage() {
    if (ammo_ <= 0){
        throw std::logic_error("No ammo.");
    }
    ammo_--;
    return INT_MAX;
}


static int heuristic(int x1, int y1, int x2, int y2) {
    return std::abs(x1 - x2) + std::abs(y1 - y2);  // Манхэттенское расстояние для сетки
}


static bool isValid(int x, int y, int mapSize) {
    return x >= 0 && x < mapSize && y >= 0 && y < mapSize;
}


static bool isWalkable(int x, int y, Matrix matr) {
    return matr[x][y].getFieldType() != fieldType::Mountain;
}


void Aviation::findPath() {
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

            if (isValid(newX, newY, mapSize) && isWalkable(newX, newY, matrix)) {
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


void Aviation::makeMove() {
    setCurrentHP(getCurrentHP() + getRegenerationRate() > getMaxHP() ? getMaxHP() : getCurrentHP() + getRegenerationRate());
    std::size_t finalStep = getCurrentStep() + getSpeed();
    auto path = getPath();
    auto matr = getLandscape()->getFieldGrid();
    if (finalStep >= path.size()) {
        finalStep = path.size() - 1;
    }

    do {
        setCurrentStep(getCurrentStep() + 1);
        auto [posX, posY] = path[getCurrentStep()];
        auto structure = matr[posX][posY].getStructure();
        if (structure != nullptr && typeid(*(structure)) == typeid(Wall) && ammo_ > 0) {
            auto wall = std::static_pointer_cast<Wall>(structure);
            wall->takeDamage(dealDamage());
        }
    } while (getCurrentStep() < finalStep);

    setPosition({path[getCurrentStep()].first, path[getCurrentStep()].second});
    /* если дошли до замка, то наносим ему урон */
    if (getCurrentStep() + 1 == path.size()) {
        auto [posX, posY] = path[getCurrentStep()];
        auto structure = matr[posX][posY].getStructure();
        auto castle = std::static_pointer_cast<Castle>(structure);
        castle->takeDamage(dealDamageToCastle());
    }
}


void Aviation::takeDamage(std::size_t damage) {
    std::size_t hp = getCurrentHP().load();
    while (hp > 0 && !getCurrentHP().compare_exchange_weak(hp, (damage > hp) ? 0 : hp - damage)) {}
}


std::shared_ptr<EnemyStats> Aviation::getStats() const {
    return std::make_shared<AviationStats>(getMaxHP(),
                                           getRegenerationRate(),
                                           getSpeed(),
                                           getAmmo());
}