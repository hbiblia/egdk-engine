# Codigo fuente del editor
set(source 
    "src/egdk-editor.c"
    "src/level-editor/level-editor.c"
    "src/level-editor/toolbar_main/ui-toolbar.c"
    "src/level-editor/viewport/docked-viewport.c"
    "src/level-editor/browser/docked-browser.c"
    "src/level-editor/browser/browserContent.c"
    "src/level-editor/browser/browserViewContent.c"
    "src/level-editor/browser/browserViewFileType.c"
    "src/level-editor/tiled/docked-tiled.c"
    "src/level-editor/gtk-renderer-embed/gtk-renderer-embed.c"
    )
    
# Cuando estemos en la etapa2 dejaremos de utilizar pkg-config
# para que sea algo mas directo con la carpeta libreria.
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK REQUIRED gtk4)
pkg_check_modules(EPOXY REQUIRED epoxy)
pkg_check_modules(SQLITE REQUIRED sqlite3)
pkg_check_modules(JSON REQUIRED json-glib-1.0)

add_executable(egdk-editor ${source})

include_directories(utility renderer ${RENDERER_INCLUDE_DIRS} ${GTK_INCLUDE_DIRS} ${EPOXY_INCLUDE_DIRS} ${SQLITE_INCLUDE_DIRS} ${JSON_INCLUDE_DIRS})
link_directories(utility renderer ${GTK_LIBRARY_DIRS} ${EPOXY_LIBRARY_DIRS} ${SQLITE_LIBRARY_DIRS} ${JSON_LIBRARY_DIRS})

target_link_libraries(egdk-editor utility renderer ${GTK_LIBRARIES} ${EPOXY_LIBRARIES} ${SQLITE_LIBRARIES} ${JSON_LIBRARIES})
