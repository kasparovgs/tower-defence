cmake_minimum_required(VERSION 3.16)
project (globalTime)

set(CMAKE_CXX_STANDARD 20)

add_library(globalTime STATIC source/globalTime.cpp)

target_include_directories(globalTime PUBLIC include)