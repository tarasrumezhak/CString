cmake_minimum_required(VERSION 3.13)

project(cstringstest)

include_directories("${CMAKE_SOURCE_DIR}/include")

file(GLOB sources "${CMAKE_SOURCE_DIR}/library/*.c")
list(REMOVE_ITEM sources "${CMAKE_SOURCE_DIR}/main.c")

file(GLOB tests "${PROJECT_SOURCE_DIR}/*.cc")
list(REMOVE_ITEM tests "${PROJECT_SOURCE_DIR}/main.cc")

foreach(file ${tests})
  set(name)
  message("found - ${file}")
  get_filename_component(name ${file} NAME_WE)
  add_executable("${name}_tests" ${sources} ${file} "${PROJECT_SOURCE_DIR}/main.cc")
  target_link_libraries("${name}_tests" gtest_main)
  add_test(NAME ${name} COMMAND "${name}_tests")
endforeach()
