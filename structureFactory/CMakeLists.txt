cmake_minimum_required(VERSION 3.16)
project(structureFactory)

set(CMAKE_CXX_STANDARD 20)

add_library(structureFactory STATIC source/structureFactory.cpp)

target_include_directories(structureFactory PUBLIC include)

target_link_libraries(structureFactory PUBLIC structure lair tower wall castle) #