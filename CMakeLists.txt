cmake_minimum_required(VERSION 3.16)
project (towerDefence)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -g")

if(BUILD_TESTING)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")
endif()

add_subdirectory(allExceptions)
add_subdirectory(mymatrix)
add_subdirectory(globalTime)
add_subdirectory(globalGold)
add_subdirectory(IDamageable)
add_subdirectory(dealDamage)
add_subdirectory(structure)
add_subdirectory(allStructures)
add_subdirectory(structureFactory)
add_subdirectory(upgradeManager)
add_subdirectory(enemy)
add_subdirectory(allEnemies)
add_subdirectory(game)
add_subdirectory(landscape)
add_subdirectory(aura)
add_subdirectory(allAuras)

if(GUI)
    add_subdirectory(gui)
    add_executable(towerDefenceExecutable source/main.cpp)
    target_link_libraries(towerDefenceExecutable PRIVATE sfml-graphics sfml-window sfml-system game visualEnemy gameRenderer upgradeManager GameOverException)
endif()


if(BUILD_TESTING)
    add_subdirectory(tests)
endif()