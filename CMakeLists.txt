# cmake_minimum_required(VERSION <specify CMake version here>)
project(. C)

set(CMAKE_C_STANDARD 99)

add_library(. SHARED library.c library.h)