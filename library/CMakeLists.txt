project(ExportedLib)

if(NOT UNIX)
add_library(ExportedLib STATIC SHARED export.cpp)
else() 
add_library(ExportedLib SHARED export.cpp)
endif()

#set the output name. Example: dll -> libdll.so
set_target_properties(ExportedLib PROPERTIES
    OUTPUT_NAME ${PROJECT_DLL_NAME})
