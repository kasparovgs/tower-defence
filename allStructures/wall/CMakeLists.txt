cmake_minimum_required(VERSION 3.16)
project (wall)

set(CMAKE_CXX_STANDARD 20)

add_library(wall STATIC source/wall.cpp)

target_include_directories(wall PUBLIC include)
target_link_libraries(wall PUBLIC structure dealDamage structureFactory)