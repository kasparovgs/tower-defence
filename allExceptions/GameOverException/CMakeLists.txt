cmake_minimum_required(VERSION 3.16)
project(GameOverException)

set(CMAKE_CXX_STANDARD 20)

add_library(GameOverException INTERFACE)

target_include_directories(GameOverException INTERFACE include)