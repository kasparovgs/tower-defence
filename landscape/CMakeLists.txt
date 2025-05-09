cmake_minimum_required(VERSION 3.16)
project(landscape)

set(CMAKE_CXX_STANDARD 20)

add_library(landscape STATIC source/landscape.cpp)

target_include_directories(landscape PUBLIC include)

target_link_libraries(landscape PUBLIC structure enemy lair structureFactory mymatrix globalGold)
find_package(TBB REQUIRED)
target_link_libraries(landscape PUBLIC TBB::tbb)
