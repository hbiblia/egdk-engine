
if(CMAKE_SYSTEM_NAME STREQUAL Windows)
set(link_renderer kernel32 user32 shell32 gdi32 ole32)
endif()

include_directories(${egdkProject_SOURCE_DIR}/src/library/renderer/inc/)
add_library(renderer STATIC renderer.c rcamera.c rmath.c rshape.c rtransform.c)
target_link_libraries(renderer ${link_renderer})