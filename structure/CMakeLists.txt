cmake_minimum_required(VERSION 3.16)
project(structure)

set(CMAKE_CXX_STANDARD 20)

add_library(structure INTERFACE)

target_include_directories(structure INTERFACE include)
target_link_libraries(structure INTERFACE landscape)