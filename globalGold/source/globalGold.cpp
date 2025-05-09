#include "globalGold.h"


std::size_t GlobalGold::gold_ = 0;
std::weak_ptr<Structure> GlobalGold::castle_;

void GlobalGold::setGold(std::size_t gold) {
    gold_ = gold;
}


std::size_t GlobalGold::getGold() {
    return gold_;
}


void GlobalGold::collectAccumulatedGold() {
    if (auto strongCastle = castle_.lock()) {
        auto castedCastle = std::static_pointer_cast<Castle>(strongCastle);
        gold_ += castedCastle->collectAccumulatedGold();
    }
}