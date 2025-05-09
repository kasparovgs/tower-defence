cmake_minimum_required(VERSION 3.16)
project(enemy)

set(CMAKE_CXX_STANDARD 20)

add_library(enemy INTERFACE)

target_include_directories(enemy INTERFACE include)
target_link_libraries(enemy INTERFACE aura landscape IDamageable)