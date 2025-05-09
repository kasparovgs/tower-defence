cmake_minimum_required(VERSION 3.16)
project (globalGold)

set(CMAKE_CXX_STANDARD 20)

add_library(globalGold STATIC source/globalGold.cpp)

target_include_directories(globalGold PUBLIC include)
target_link_libraries(globalGold PUBLIC castle)