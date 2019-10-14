cmake_minimum_required(VERSION 3.13)

project(cstrings)

set(CMAKE_C_STANDARD 99)

configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)

execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )

add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
        ${CMAKE_BINARY_DIR}/googletest-build)

enable_testing()
add_subdirectory(test)

file(GLOB sources "${PROJECT_SOURCE_DIR}/*.h" "${PROJECT_SOURCE_DIR}/*.c")
list(REMOVE_ITEM tests "${PROJECT_SOURCE_DIR}/main.c")

include_directories("${PROJECT_SOURCE_DIR}")

add_library(cstrings SHARED ${sources})
