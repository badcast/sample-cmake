project(ExportedLib)

add_library(ExportedLib SHARED export.cpp)

#set the output name. Example: dll -> libdll.so
set_target_properties(ExportedLib PROPERTIES OUTPUT_NAME "dll")
