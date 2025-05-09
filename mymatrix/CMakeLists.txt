cmake_minimum_required(VERSION 3.16)
project(mymatrix)

set(CMAKE_CXX_STANDARD 20)

add_library(mymatrix INTERFACE)

target_include_directories(mymatrix INTERFACE include)