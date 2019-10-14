cmake_minimum_required(VERSION 3.13)

project(cstringstest)

include_directories("..")

file(GLOB sources "../*.c")
list(REMOVE_ITEM sources "../main.c")

file(GLOB tests "../test/*.cc")
list(REMOVE_ITEM tests "../test/main.cc")

foreach(file ${tests})
  set(name)
  get_filename_component(name ${file} NAME_WE)
  add_executable("${name}_tests"
    ${sources}
    ${file}
    "../test/main.cc")
  target_link_libraries("${name}_tests" gtest_main)
  add_test(NAME ${name} COMMAND "${name}_tests")
endforeach()
