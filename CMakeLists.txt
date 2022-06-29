cmake_minimum_required(VERSION 3.2)

project(sample_cmake LANGUAGES CXX)

set(BINARY_DIR ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BINARY_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/lib)
set(PROJECT_DLL_NAME "dll") 

#compile library to local path: libdll.so

add_subdirectory(library/)

#create a var dll as lib
add_library(dll SHARED IMPORTED) 

#set imported location
if(NOT UNIX)
set_target_properties(dll PROPERTIES
    IMPORTED_IMPLIB ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/${PROJECT_DLL_NAME}
    IMPORTED_IMPLIB_DEBUG ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/${PROJECT_DLL_NAME}
    IMPORTED_IMPLIB_RELEASE ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/${PROJECT_DLL_NAME}
    IMPORTED_LOCATION "${PROJECT_DLL_NAME}.dll"
    IMPORTED_CONFIGURATIONS "RELEASE;DEBUG") # get library from current location)
else()
    get_target_property(libsoname ExportedLib OUTPUT_NAME)
    message(fatal_error ${libsoname})
set_target_properties(dll PROPERTIES
    IMPORTED_LOCATION "lib${PROJECT_DLL_NAME}.so")# get library from current location
endif()

add_executable(sample_cmake import.h main.cpp)

target_link_libraries(sample_cmake dll)
