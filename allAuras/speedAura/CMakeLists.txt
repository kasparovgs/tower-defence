cmake_minimum_required(VERSION 3.16)
project(speedAura)

set(CMAKE_CXX_STANDARD 20)

add_library(speedAura STATIC source/speedAura.cpp)

target_include_directories(speedAura PUBLIC include)

target_link_libraries(speedAura PUBLIC aura)