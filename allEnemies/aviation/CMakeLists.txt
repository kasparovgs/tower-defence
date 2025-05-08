cmake_minimum_required(VERSION 3.16)
project (aviation)

set(CMAKE_CXX_STANDARD 20)

add_library(aviation STATIC source/aviation.cpp)

target_include_directories(aviation PUBLIC include)
target_link_libraries(aviation PUBLIC enemy dealDamage)