cmake_minimum_required(VERSION 3.2)

project(sample_cmake VERSION 1.0 LANGUAGES CXX)

set(BINARY_DIR ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BINARY_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/lib)
set(PROJECT_DLL_NAME "sample_lib")

#compile library to local path: libdll.so
add_library(sample_lib SHARED include/import.h sample_lib/sample_library.cpp)

#create a var dll as lib
add_library(linkdll SHARED IMPORTED)

if(WIN32)
    #set imported location
    if(MSVC)
        file(GLOB_RECURSE LIB_STATIC_EXPORTED "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/*${PROJECT_DLL_NAME}.lib")
    else(CMAKE_COMPILER_IS_GNUCXX) # GCC compiller
        file(GLOB_RECURSE LIB_STATIC_EXPORTED "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/*${PROJECT_DLL_NAME}.dll.a")
    endif()

    set_target_properties(linkdll PROPERTIES 
        IMPORTED_IMPLIB "${LIB_STATIC_EXPORTED}"
        IMPORTED_LOCATION "*${PROJECT_DLL_NAME}")

else(UNIX)
    set_target_properties(linkdll PROPERTIES
        IMPORTED_LOCATION "./lib${PROJECT_DLL_NAME}.so")# get library from current location
endif()

include_directories(include/)

add_executable(sample_bin include/import.h sample_bin/sample_bin.cpp)

target_link_libraries(sample_bin linkdll)

