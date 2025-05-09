cmake_minimum_required(VERSION 3.16)
project(upgradeManager)

set(CMAKE_CXX_STANDARD 20)

add_library(upgradeManager STATIC source/upgradeManager.cpp)

target_include_directories(upgradeManager PUBLIC include)

target_link_libraries(upgradeManager PUBLIC structure lair tower wall castle globalGold)