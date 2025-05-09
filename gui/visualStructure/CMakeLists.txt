cmake_minimum_required(VERSION 3.16)
project (visualStructure)

set(CMAKE_CXX_STANDARD 20)

add_library(visualStructure STATIC source/visualStructure.cpp)

target_include_directories(visualStructure PUBLIC include)
target_link_libraries(visualStructure PUBLIC structure)