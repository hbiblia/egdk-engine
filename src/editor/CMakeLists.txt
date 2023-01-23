# Codigo fuente del editor
set(source 
    "src/egdk-editor.c"
    "src/ui-editor-main.c"
    "src/ui-editor-menubar.c"
    "src/ui-docked-viewport.c"
    "src/ui-docked-hierarchy.c"
    "src/ui-docked-inspector.c"
    "src/ui-docked-browser.c"
    "src/editor-browser.c"
    )
    
# Cuando estemos en la etapa2 dejaremos de utilizar pkg-config
# para que sea algo mas directo con la carpeta libreria.
find_package(PkgConfig REQUIRED)
# pkg_check_modules(JSON REQUIRED json-glib-1.0)
pkg_check_modules(GLIB REQUIRED glib-2.0)

add_executable(egdk-editor ${source})

include_directories(utility pixel lua ${RENDERER_INCLUDE_DIRS} ${GLIB_INCLUDE_DIRS})
link_directories(utility pixel lua ${GLIB_LIBRARY_DIRS})

target_link_libraries(egdk-editor utility pixel lua ${GLIB_LIBRARIES})
