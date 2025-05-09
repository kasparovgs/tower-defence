cmake_minimum_required(VERSION 3.16)
project(lair)

set(CMAKE_CXX_STANDARD 20)

add_library(lair STATIC source/lair.cpp)

target_include_directories(lair PUBLIC include)

target_link_libraries(lair PUBLIC structure dealDamage aviation lightInfantry heavyInfantry hero globalTime structureFactory)