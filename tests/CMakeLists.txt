cmake_minimum_required(VERSION 3.16)
project(towerDefense_tests)

enable_testing()

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")

find_package(GTest REQUIRED)

add_executable(all_tests
    lightInfantry_tests.cpp
    heavyInfantry_tests.cpp
    aviation_tests.cpp
    lair_tests.cpp
    game_tests.cpp
    structureFactory_tests.cpp
    landscape_tests.cpp
    hero_tests.cpp
    tower_tests.cpp
    castle_tests.cpp
    wall_tests.cpp
    auras_tests.cpp
    mymatrix_tests.cpp
    # остальные тестовые файлы добавить
)

target_link_libraries(all_tests 
                      GTest::gtest
                      GTest::gtest_main
                      lightInfantry
                      heavyInfantry
                      hero
                      aviation
                      game
                      lair
                      structureFactory
                      landscape
                      wall
                      tower
                      castle
                      aura
                      maxhpAura
                      regenerationAura
                      speedAura
                      mymatrix)

add_test(NAME all_tests COMMAND all_tests)