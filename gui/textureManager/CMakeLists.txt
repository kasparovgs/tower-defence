cmake_minimum_required(VERSION 3.16)
project (textureManager)

set(CMAKE_CXX_STANDARD 20)

add_library(textureManager STATIC source/textureManager.cpp)

target_include_directories(textureManager PUBLIC include)
# target_link_libraries(textureManager PUBLIC game visualLair)