#ifndef GLOBALTIME_H
#define GLOBALTIME_H

#include <iostream>

class GlobalTime {
private:
    static std::size_t time_;
public:
    static void updateTime();
    static void setTime(std::size_t time);
    static std::size_t getTime();
};


#endif