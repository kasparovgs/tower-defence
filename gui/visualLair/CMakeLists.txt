cmake_minimum_required(VERSION 3.16)
project (visualLair)

set(CMAKE_CXX_STANDARD 20)

add_library(visualLair STATIC source/visualLair.cpp)

target_include_directories(visualLair PUBLIC include)
target_link_libraries(visualLair PUBLIC aviation lightInfantry heavyInfantry hero visualEnemy textureManager)