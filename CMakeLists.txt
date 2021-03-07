cmake_minimum_required(VERSION 3.19)
project(Bilging)

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "/usr/local/Cellar/gcc/10.2.0_4/bin/g++-10")

set(CMAKE_VERBOSE_MAKEFILE OFF)
set(CMAKE_CXX_STANDARD 20)

set (CMAKE_CXX_FLAGS "-fopenmp -Ofast -march=native")

add_executable(Bilging main.cpp Board.cpp Searcher.cpp)