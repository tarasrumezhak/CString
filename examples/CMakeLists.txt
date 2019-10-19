cmake_minimum_required(VERSION 3.13)

project(example)

include_directories("${CMAKE_SOURCE_DIR}/include")
link_directories("${CMAKE_BINARY_DIR}")

add_executable(example main.c example.c)
add_executable(test_functions test_functions.c)
target_link_libraries(example cstrings)
target_link_libraries(test_functions cstrings)
