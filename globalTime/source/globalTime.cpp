#include "globalTime.h"

std::size_t GlobalTime::time_ = 0;


void GlobalTime::updateTime() {
    time_ += 1;
}


void GlobalTime::setTime(std::size_t time) {
    time_ = time;
}


std::size_t GlobalTime::getTime() {
    return time_;
}