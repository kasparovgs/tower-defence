cmake_minimum_required(VERSION 3.16)
project(tower)

set(CMAKE_CXX_STANDARD 20)

add_library(tower STATIC source/tower.cpp)

target_include_directories(tower PUBLIC include)

target_link_libraries(tower PUBLIC structure dealDamage enemy structureFactory)