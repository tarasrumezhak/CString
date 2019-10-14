# cmake_minimum_required(VERSION <specify CMake version here>)
#project(. C)
#
#set(CMAKE_C_STANDARD 99)
#
#add_library(. SHARED library.c library.h main.c)

cmake_minimum_required(VERSION 3.13)
project(. C)

SET(LIB_NAME String)
SET(EXEC_NAME my_str)

set(CMAKE_C_STANDARD 99)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY  ../bin/lib)

add_library(${LIB_NAME} SHARED library.c library.h)

add_executable(${EXEC_NAME} main.c)

target_link_libraries(${EXEC_NAME} ${LIB_NAME})