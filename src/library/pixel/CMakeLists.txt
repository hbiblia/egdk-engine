if(CMAKE_SYSTEM_NAME STREQUAL Windows)
add_compile_definitions(SOKOL_D3D11)
add_compile_definitions(WINDOWS)
set(link_deps kernel32 user32 shell32 dxgi d3d11 ole32 gdi32)
endif()

find_package(PkgConfig REQUIRED)
pkg_check_modules(GLIB REQUIRED glib-2.0)

include_directories(${GLIB_INCLUDE_DIRS})
link_directories(${GLIB_LIBRARY_DIRS})

add_library(pixel STATIC 
    pixel.c
    pixel-ecs.c
    )
    
target_link_libraries(pixel flecs cimgui utility ${link_deps} ${GLIB_LIBRARIES})
target_compile_options(pixel PRIVATE -w -Wall -Wpedantic)