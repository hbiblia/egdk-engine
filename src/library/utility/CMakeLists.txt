
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLIB REQUIRED glib-2.0)

include_directories(${GLIB_INCLUDE_DIRS})
link_directories(${GLIB_LIBRARY_DIRS})

add_library(utility STATIC 
    file_fn.c 
    path_fn.c 
    string_fn.c
    )

target_link_libraries(utility ${GLIB_LIBRARIES})

