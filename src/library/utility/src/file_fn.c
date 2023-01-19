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

/*
 * Name: FileReaddir
 * Public
 * Params: (const char *path)
 * Return: GPtrArray *
 * Desc: Cargamos el contenido de un folder
 */
GPtrArray *FileReaddir(const char *path)
{
    GError *error = NULL;
    GDir *dir = g_dir_open(path, 0, &error);
    if (dir == NULL)
        return NULL;

    GPtrArray *cache_dir = g_ptr_array_new();
    const gchar *filename;

    while ((filename = g_dir_read_name(dir)) != NULL)
    {
        FileDirFile *file = g_new0(FileDirFile, 1);
        file->name = g_strdup(filename);
        file->path = g_strdup(path);
        file->ext = FileGetExtension(filename);

        if (g_file_test(file->name, G_FILE_TEST_IS_DIR))
        {
            file->type = FILE_FOLDER;
        }
        else if (strcmp(file->ext, "jpg")==0 || strcmp(file->ext, "png")==0)
        {
            file->type = FILE_TEXTURE;
        }
        else if (strcmp(file->ext, "lua")==0)
        {
            file->type = FILE_LUA;
        }
        else if (strcmp(file->ext, "json")==0)
        {
            file->type = FILE_JSON;
        }
        else if (strcmp(file->ext, "tiled")==0)
        {
            file->type = FILE_TILED;
        }else {
            continue;
        }

        g_ptr_array_add(cache_dir, file);
    }
    return cache_dir;
}
