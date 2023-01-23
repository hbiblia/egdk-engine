add_library(flecs STATIC flecs.c)

if(WIN32)
target_link_libraries(flecs wsock32 ws2_32)
endif()

if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
target_link_libraries(flecs pthread)
endif()