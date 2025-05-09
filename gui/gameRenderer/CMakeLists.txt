cmake_minimum_required(VERSION 3.16)
project (gameRenderer)

set(CMAKE_CXX_STANDARD 20)

add_library(gameRenderer STATIC source/gameRenderer.cpp)

target_include_directories(gameRenderer PUBLIC include)
target_link_libraries(gameRenderer PUBLIC game visualLair visualStructureFactory textureManager aviation)