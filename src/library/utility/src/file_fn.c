#include "file_fn.h"
#include "pixel/pixel.h"
#include "path_fn.h"
#include "string_fn.h"

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
 * Name: FileGetName
 * Desc: Obtenemos el nombre sin la extension
 */
const char *FileGetName(const char *filename)
{
    char **value = StringSplit(filename, ".");
    const char *result = value[0];
    StringSplitFree(value);
    return StringDup(result);
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
        file->name = FileGetName(filename);
        file->filename = StringDup(filename);
        file->path = StringDup(path);
        file->ext = FileGetExtension(filename);

        if (g_file_test(PathBuild(file->path, filename, NULL), G_FILE_TEST_IS_DIR))
        {
            file->type = FILE_FOLDER;
        }
        else if (strcmp(file->ext, "jpg") == 0 || strcmp(file->ext, "png") == 0)
        {
            file->type = FILE_TEXTURE;
        }
        else if (strcmp(file->ext, "lua") == 0)
        {
            file->type = FILE_LUA;
        }
        else if (strcmp(file->ext, "json") == 0)
        {
            file->type = FILE_JSON;
        }
        else if (strcmp(file->ext, "tiled") == 0)
        {
            file->type = FILE_TILED;
        }
        else
        {
            continue;
        }
        g_ptr_array_add(cache_dir, file);
    }
    return cache_dir;
}

/*
 * Name: FileReaddirFree
 * Public
 * Params: (GPtrArray *readder_cache)
 * Return: void
 * Desc: Liberarmos el FileReaddir
 */
void FileReaddirFree(GPtrArray *readder_cache)
{
    if (readder_cache == NULL)
        return;
        
    for (int i = 0; i < readder_cache->len; i++)
    {
        FileDirFile *file = g_ptr_array_index(readder_cache, i);
        if (file->type == FILE_TEXTURE)
        {
            pTexture_Free((pixel_texture_t){.id = file->image_id});
        }
        // g_free(file->name);
        // g_free(file->filename);
        // g_free(file->path);
        g_free(file);
    }
    g_ptr_array_free(readder_cache, TRUE);
}