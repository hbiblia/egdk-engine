#include "file_fn.h"

/*
 * Name: FileIsExtension
 * Desc: Comprobamos si un filename tiene la ext
 */
gboolean FileIsExtension(const gchar *filename, const gchar *ext)
{
    const gchar *ext_o = FileGetExtension(filename);
    return strcmp(ext_o, ext) == 0 ? TRUE : FALSE;
}

/*
 * Name: FileGetExtension
 * Desc: Obtenemos la ext de un archivo
 */
const gchar *FileGetExtension(const gchar *filename)
{
    const gchar *dot = strrchr(filename, '.');
    return (!dot || dot == filename) ? "" : (dot + 1);
}
