cmake_minimum_required(VERSION 3.19)
project(egdkProject)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

set(header_base "src/")
set(utility_src 
"../utility/file_fn.c"
"../utility/path_fn.c"
"../utility/string_fn.c"
)

# RENDERER
set(renderer_src
"../renderer/renderer.c"
"../renderer/rcamera.c"
"../renderer/rshape.c"
"../renderer/rtransform.c"
)
if(CMAKE_SYSTEM_NAME STREQUAL Windows)
    set(link_renderer kernel32 user32 shell32 gdi32 ole32)
endif()

include_directories(src/ src/library/sokol/src/)

add_subdirectory(src/editor)
add_subdirectory(src/game)
