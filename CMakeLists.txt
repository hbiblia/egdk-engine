cmake_minimum_required(VERSION 3.19)
project(egdkProject)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

include_directories( 
    src/library/gtk-sokol/inc/
    src/library/renderer/inc/
    src/library/utility/inc/
 )

# 
add_subdirectory(src/library/utility)
add_subdirectory(src/library/renderer)
add_subdirectory(src/editor)
add_subdirectory(src/game)
