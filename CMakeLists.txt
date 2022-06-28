cmake_minimum_required(VERSION 3.2)

project(sample_cmake LANGUAGES CXX)

set(BINARY_DIR "${CMAKE_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${BINARY_DIR}")

#compile library to local path: bin/libdll.so
add_subdirectory(library/)

#create a var dll as lib
add_library(dll SHARED IMPORTED)

#set imported location
set_target_properties(dll PROPERTIES
    IMPORTED_LOCATION "./libdll.so") # get library from current location

add_executable(sample_cmake import.h main.cpp)

target_link_libraries(sample_cmake dll)
