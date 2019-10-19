cmake_minimum_required(VERSION 3.13)

project(example)

file(GLOB sources "${PROJECT_SOURCE_DIR}/*.c")

include_directories("${CMAKE_SOURCE_DIR}/include")
link_directories("${CMAKE_BINARY_DIR}")

add_executable(example ${sources})

target_link_libraries(example cstrings)
