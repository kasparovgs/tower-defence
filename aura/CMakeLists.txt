cmake_minimum_required(VERSION 3.16)
project(aura)

set(CMAKE_CXX_STANDARD 20)

add_library(aura INTERFACE)

target_include_directories(aura INTERFACE include)
target_link_libraries(aura INTERFACE enemy)