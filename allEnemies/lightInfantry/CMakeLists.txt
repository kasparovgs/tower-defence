cmake_minimum_required(VERSION 3.16)
project (lightInfantry)

set(CMAKE_CXX_STANDARD 20)

add_library(lightInfantry STATIC source/lightInfantry.cpp)

target_include_directories(lightInfantry PUBLIC include)
target_link_libraries(lightInfantry PUBLIC enemy)