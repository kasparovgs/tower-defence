cmake_minimum_required(VERSION 3.16)
project(regenerationAura)

set(CMAKE_CXX_STANDARD 20)

add_library(regenerationAura STATIC source/regenerationAura.cpp)

target_include_directories(regenerationAura PUBLIC include)

target_link_libraries(regenerationAura PUBLIC aura)