cmake_minimum_required(VERSION 3.16)
project (hero)

set(CMAKE_CXX_STANDARD 20)

add_library(hero STATIC source/hero.cpp)

target_include_directories(hero PUBLIC include)
target_link_libraries(hero PUBLIC enemy dealDamage lightInfantry heavyInfantry aviation maxhpAura speedAura regenerationAura)