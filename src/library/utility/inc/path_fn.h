#ifndef PATH_FN_H
#define PATH_FN_H
#include <stdio.h>

/*
 * Name: PathNormalize
 * Private
 * Params: (const char *path)
 * Return: char *
 * Desc: Normalizamos el path
 */
char *PathNormalize(const char *path);

/*
 * Name: PathPwd
 * Private
 * Params: (void)
 * Return: const char *
 * Desc: Obtenemos la ruta donde estamos en el sistema
 */
const char *PathPwd(void);

/*
 * Name: PathBuild
 * Private
 * Params: (const char *path, ...)
 * Return: char *
 * Desc: Concatenamos un path y lo normalizamos
 */
char *PathBuild(const char *path, ...);

#endif