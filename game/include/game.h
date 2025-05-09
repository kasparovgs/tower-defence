#ifndef GAME_H
#define GAME_H

#include <string>
#include <memory>
#include "landscape.h"
#include "globalTime.h"
#include "globalGold.h"

class Game{
private:
    std::size_t level_ = 1;
    std::shared_ptr<Landscape> landscape_;
public:
    Game();
    ~Game() { landscape_.reset(); }
    void initGame(const std::string& filePath);
    void makeMove();

    [[nodiscard]] auto getEnemies() const { return landscape_->getEnemies(); }
    [[nodiscard]] auto getStructures() const { return landscape_->getStructures(); }

    [[nodiscard]] std::size_t getLevel() const { return level_; }
    [[nodiscard]] auto getCastle() const { return landscape_->getStructureByPosition(landscape_->getCastlePosition()); }
    [[nodiscard]] const std::shared_ptr<Landscape>& getLandscape() const { return landscape_; }
};




#endif