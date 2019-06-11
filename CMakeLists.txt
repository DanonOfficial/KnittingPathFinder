cmake_minimum_required(VERSION 3.13)
project(KnittingPathFinder)

set(CMAKE_CXX_STANDARD 17)

add_executable(KnittingPathFinder src/main.cpp include/PathFinder.hpp src/PathFinder.cpp)