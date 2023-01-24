cmake_minimum_required(VERSION 3.19)
project(egdkProject)
set(CMAKE_C_STANDARD 99)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

include_directories( 
    src/library/utility/inc/
    src/library/lua/src/
    src/library/
 )

# 
add_subdirectory(src/library/utility)
add_subdirectory(src/library/pixel)
add_subdirectory(src/library/cimgui)
add_subdirectory(src/library/lua)
add_subdirectory(src/library/flecs)
add_subdirectory(src/editor)
add_subdirectory(src/game)
