cmake_minimum_required(VERSION 3.13)

project(cstringstest)

include_directories("${CMAKE_SOURCE_DIR}/include")

file(GLOB sources "${CMAKE_SOURCE_DIR}/library/*.c")

list(REMOVE_ITEM sources "${CMAKE_SOURCE_DIR}/main.c")

file(GLOB tests "${PROJECT_SOURCE_DIR}/library.cc")
list(REMOVE_ITEM tests "${PROJECT_SOURCE_DIR}/main.cc")

add_executable(library_tests ${sources} "library.cc" "main.cc")

add_test(NAME "library" COMMAND "library_tests")
target_link_libraries(library_tests gtest_main)
