#ifndef GLOBALGOLD_H
#define GLOBALGOLD_H

#include <iostream>
#include <memory>
#include "castle.h"

class GlobalGold {
private:
    static std::size_t gold_;
    static std::weak_ptr<Structure> castle_;
public:
    static void setGold(std::size_t gold);
    static std::size_t getGold();
    static void setCastle(std::shared_ptr<Structure> castle) { castle_ = castle; }
    static void collectAccumulatedGold();
};


#endif