#include <glib.h>
#include "path_fn.h"
#include "string_fn.h"

/*
 * Name: PathNormalize
 * Desc: Normalizamos el path
 */
char *PathNormalize(const char *path)
{
    char *new_path = NULL;
#if defined(_WIN32)
    new_path = StringReplace(path, "/", "\\");
#else
    new_path = StringReplace(path, "\\", "/");
#endif
    return new_path;
}

/*
 * Name: PathPwd
 * Desc: Obtenemos la ruta donde estamos en el sistema
 */
const char *PathPwd(void)
{
    return g_get_current_dir();
}

/*
 * Name: PathBuild
 * Desc: Concatenamos un path y lo normalizamos
 */
char *PathBuild(const char *path, ...)
{
    return PathNormalize(g_build_filename(path));
}