cmake_minimum_required(VERSION 3.16)
project(castle)

set(CMAKE_CXX_STANDARD 20)

add_library(castle STATIC source/castle.cpp)

target_include_directories(castle PUBLIC include)

target_link_libraries(castle PUBLIC structure enemy IDamageable GameOverException structureFactory)