cmake_minimum_required(VERSION 3.13)

project(cstrings)

file(GLOB sources "${CMAKE_SOURCE_DIR}/library/*.c")

include_directories("${CMAKE_SOURCE_DIR}/include")

add_library(cstrings SHARED ${sources})
