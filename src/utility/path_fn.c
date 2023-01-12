#include "path_fn.h"
#include "string_fn.h"

/*
 * Name: PathNormalize
 * Private
 * Params: (const char *path)
 * Return: char *
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