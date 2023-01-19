if(CMAKE_SYSTEM_NAME STREQUAL Windows)
add_compile_definitions(SOKOL_D3D11)
add_compile_definitions(WINDOWS)
set(link_deps kernel32 user32 shell32 dxgi d3d11 ole32 gdi32)
endif()

include_directories(${egdkProject_SOURCE_DIR}/src/library/pixel/inc/)
add_library(pixel STATIC 
    pixel.c
    pixel-gfx.c
    pixel-camera.c
    pixel-math.c
    pixel-shape.c
    pixel-transform.c
    pixel-window.c
    pixel-gui.c
    )
target_link_libraries(pixel cimgui ${link_deps})
target_compile_options(pixel PRIVATE -w -Wall -Wpedantic)