cmake_minimum_required(VERSION 3.16)
project(maxhpAura)

set(CMAKE_CXX_STANDARD 20)

add_library(maxhpAura STATIC source/maxhpAura.cpp)

target_include_directories(maxhpAura PUBLIC include)

target_link_libraries(maxhpAura PUBLIC aura)