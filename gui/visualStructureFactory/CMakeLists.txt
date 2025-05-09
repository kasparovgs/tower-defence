cmake_minimum_required(VERSION 3.16)
project (visualStructureFactory)

set(CMAKE_CXX_STANDARD 20)

add_library(visualStructureFactory STATIC source/visualStructureFactory.cpp)

target_include_directories(visualStructureFactory PUBLIC include)
target_link_libraries(visualStructureFactory PUBLIC wall lair tower castle visualStructure textureManager)