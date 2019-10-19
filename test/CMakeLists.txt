cmake_minimum_required(VERSION 3.13)

project(cstringstest)

include_directories("${CMAKE_SOURCE_DIR}/include")
include_directories("${CMAKE_SOURCE_DIR}/examples")

file(GLOB sources "${CMAKE_SOURCE_DIR}/library/*.c")
add_library(objs OBJECT ${sources})

file(GLOB tests "${PROJECT_SOURCE_DIR}/*.cc")
list(REMOVE_ITEM tests "${PROJECT_SOURCE_DIR}/main.cc" "${PROJECT_SOURCE_DIR}/example.cc")

add_executable(example_tests $<TARGET_OBJECTS:objs>
  "${CMAKE_SOURCE_DIR}/examples/example.c"
  "${PROJECT_SOURCE_DIR}/example.cc"
  "${PROJECT_SOURCE_DIR}/main.cc")
target_link_libraries(example_tests gtest_main)
add_test(NAME example COMMAND example_tests)

foreach(file ${tests})
  set(name)
  message("found - ${file}")
  get_filename_component(name ${file} NAME_WE)
  add_executable("${name}_tests" $<TARGET_OBJECTS:objs> ${file} "${PROJECT_SOURCE_DIR}/main.cc")
  target_link_libraries("${name}_tests" gtest_main)
  add_test(NAME ${name} COMMAND "${name}_tests")
endforeach()
