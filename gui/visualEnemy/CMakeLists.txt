cmake_minimum_required(VERSION 3.16)
project (visualEnemy)

set(CMAKE_CXX_STANDARD 20)

add_library(visualEnemy STATIC source/visualEnemy.cpp)

target_include_directories(visualEnemy PUBLIC include)
target_link_libraries(visualEnemy PUBLIC enemy)