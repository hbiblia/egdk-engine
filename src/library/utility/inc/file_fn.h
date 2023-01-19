#ifndef FILE_FN_H
#define FILE_FN_H
#include <stdio.h>
#include <glib.h>

typedef enum
{
    FILE_FOLDER,
    FILE_TEXTURE,
    FILE_LUA,
    FILE_JSON,
    FILE_TILED
} FileTypeSupport;

typedef struct
{
    const char *name;
    const char *ext;
    const char *path;
    FileTypeSupport type;
} FileDirFile;

/*
 * Name: FileIsExtension
 * Public
 * Params: (const gchar *filename)
 * Return: gboolean
 * Desc: Comprobamos si un filename tiene la ext
 */
gboolean FileIsExtension(const gchar *filename, const gchar *ext);

/*
 * Name: FileGetExtension
 * Public
 * Params: (const gchar *filename)
 * Return: const gchar *
 * Desc: Obtenemos la ext de un archivo
 */
const gchar *FileGetExtension(const gchar *filename);

/*
 * Name: FileReaddir
 * Public
 * Params: (const char *path)
 * Return: GPtrArray *
 * Desc: Cargamos el contenido de un folder
 */
GPtrArray *FileReaddir(const char *path);

#endif