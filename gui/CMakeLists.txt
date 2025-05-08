cmake_minimum_required(VERSION 3.16)
project(gui)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(gameRenderer)
add_subdirectory(visualLair)
add_subdirectory(visualEnemy)
add_subdirectory(visualStructureFactory)
add_subdirectory(visualStructure)
add_subdirectory(textureManager)
# add_library(gui STATIC source/main.cpp)

# #target_include_directories(gui PUBLIC include)

# add_executable(towerDefenceExecutable source/main.cpp)

# target_link_libraries(towerDefenceExecutable PRIVATE sfml-graphics sfml-window sfml-system game visualEnemy gameRenderer)

# find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# # add_executable(towerDefenceExecutable source/main.cpp)

# target_link_libraries(towerDefenceExecutable PRIVATE gui)

# target_link_libraries(towerDefenceExecutable PRIVATE game)

