cmake_minimum_required(VERSION 3.13)

project(CStrings)


SET(LIB_NAME String)
SET(EXEC_NAME my_str)

set(CMAKE_C_STANDARD 99)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY  ../bin/lib)

add_library(${LIB_NAME} SHARED library.c library.h)

add_executable(${EXEC_NAME} main.c)

include_directories(".")
add_library(. SHARED library.c library.h main.c)

configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)

execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )

add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
        ${CMAKE_BINARY_DIR}/googletest-build)

enable_testing()
add_subdirectory(test)

target_link_libraries(${EXEC_NAME} ${LIB_NAME})
