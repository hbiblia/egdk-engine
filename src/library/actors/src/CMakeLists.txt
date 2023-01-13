
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLIB REQUIRED glib-2.0)
pkg_check_modules(GOBJECT REQUIRED gobject-2.0)

include_directories(${GLIB_INCLUDE_DIRS} ${GOBJECT_INCLUDE_DIRS})
link_directories(${GLIB_LIBRARY_DIRS} ${GOBJECT_LIBRARY_DIRS})

add_library(ACTORS STATIC actor_node.c node_shape_rect.c)

include_directories(${egdkProject_SOURCE_DIR}/src/library/actors/inc/)
target_link_libraries(ACTORS ${GLIB_LIBRARIES} ${GOBJECT_LIBRARIES})