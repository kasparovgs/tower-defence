cmake_minimum_required(VERSION 3.16)
project (game)

set(CMAKE_CXX_STANDARD 20)

add_library(game STATIC source/game.cpp)

target_include_directories(game PUBLIC include)
target_link_libraries(game PUBLIC landscape enemy globalTime globalGold)