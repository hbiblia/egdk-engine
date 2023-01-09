# Codigo fuente del editor
set(source 
    "src/egdk-editor.c"
    "src/level-editor/level-editor.c"
    "src/level-editor/toolbar_main/ui-toolbar.c"
    "src/level-editor/viewport/docked-viewport.c"
    "src/level-editor/browser/docked-browser.c"
    "src/level-editor/browser/browserViewFileType.c"
    "src/level-editor/tiled/docked-tiled.c"
    )
    
# Cuando estemos en la etapa2 dejaremos de utilizar pkg-config
# para que sea algo mas directo con la carpeta libreria.
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK REQUIRED gtk4)
pkg_check_modules(EPOXY REQUIRED epoxy)

add_executable(egdk-editor ${source})

include_directories(${GTK_INCLUDE_DIRS} ${EPOXY_INCLUDE_DIRS})
link_directories(${GTK_LIBRARY_DIRS} ${EPOXY_LIBRARY_DIRS})

#target_include_directories(egdk-editor PUBLIC ${CMAKE_INCLUDE_CURRENT_DIR}/library)
#target_link_directories(egdk-editor PUBLIC ${CMAKE_INCLUDE_CURRENT_DIR}/library)

target_link_libraries(egdk-editor ${GTK_LIBRARIES} ${EPOXY_LIBRARIES})
