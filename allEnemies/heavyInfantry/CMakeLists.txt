cmake_minimum_required(VERSION 3.16)
project (heavyInfantry)

set(CMAKE_CXX_STANDARD 20)

add_library(heavyInfantry STATIC source/heavyInfantry.cpp)

target_include_directories(heavyInfantry PUBLIC include)
target_link_libraries(heavyInfantry PUBLIC enemy dealDamage wall)