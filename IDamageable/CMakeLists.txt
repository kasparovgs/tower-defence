cmake_minimum_required(VERSION 3.16)
project(IDamageable)

set(CMAKE_CXX_STANDARD 20)

add_library(IDamageable INTERFACE)

target_include_directories(IDamageable INTERFACE include)