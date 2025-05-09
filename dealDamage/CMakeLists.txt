cmake_minimum_required(VERSION 3.16)
project(dealDamage)

set(CMAKE_CXX_STANDARD 20)

add_library(dealDamage INTERFACE)

target_include_directories(dealDamage INTERFACE include)