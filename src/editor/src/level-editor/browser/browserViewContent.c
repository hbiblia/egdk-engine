
#include "browserViewContent.h"
#include "browserContent.h"
#include "browserViewFileType.h"
#include "utility/path_fn.h"
#include "utility/file_fn.h"

const gchar *path_current = "";

typedef struct
{
    gchar *name;
    gchar *path;
    BrowserFileType type;
} BrowserViewContentFile;


/*
 * Name: browserViewContentDirPath
 * Private
 * Params: (const gchar *path)
 * Return: GPtrArray*
 * Desc: Cargamos el contenido de un folder en el content
 */
static GPtrArray *browserViewContentDirPath(const gchar *path)
{
    GDir *dir;
    GError *error = NULL;
    const gchar *filename;

    GPtrArray *array = g_ptr_array_new();

    const gchar *project_path = g_build_filename(BROWSER_GET_PATH_CONTENT, path, NULL);
    dir = g_dir_open(project_path, 0, &error);
    if (dir == NULL)
    {
        fprintf(stderr, "Error abriendo el directorioL %s\n", error->message);
        g_error_free(error);
        return NULL;
    }

    while ((filename = g_dir_read_name(dir)) != NULL)
    {
        BrowserViewContentFile *file = g_new0(BrowserViewContentFile, 1);
        file->name = g_strdup(filename);
        file->path = PathNormalize(g_build_filename(project_path, filename, NULL));

        if (g_file_test(file->path, G_FILE_TEST_IS_DIR))
        {
            file->type = BROWSER_FILE_T_FOLDER;
        }
        else if (FileIsExtension(file->path, "jpg") || FileIsExtension(file->path, "png"))
        {
            file->type = BROWSER_FILE_T_TEXTURE;
        }
        else if (FileIsExtension(file->path, "lua"))
        {
            file->type = BROWSER_FILE_T_LUA;
        }
        else if (FileIsExtension(file->path, "tiled"))
        {
            file->type = BROWSER_FILE_T_TILED;
        }
        else if (FileIsExtension(file->path, "json"))
        {
            file->type = BROWSER_FILE_T_JSON;
        }
        else
        {
            file->type = BROWSER_FILE_NULL;
        }

        g_ptr_array_add(array, file);
    }

    return array;
}

/*
 * Name: browserViewContentSetPathCurrent
 * Private
 * Params: (const gchar *path)
 * Return: void
 * Desc: Asignamos el path_current
 */
void browserViewContentSetPathCurrent(const gchar *path)
{
    path_current = g_strdup(path);
}

/*
 * Name: browserViewContentDirCurrentPath
 * Private
 * Params: (GListStore *store)
 * Return: void
 * Desc: Listamos los archivos del path_current
 */
void browserViewContentDirCurrentPath(GListStore *store, const gchar *filter)
{
    GPtrArray *dir_content = browserViewContentDirPath(path_current);

    browserViewContentClear(store);

    for (int i = 0; i < dir_content->len; i++)
    {
        BrowserViewContentFile *file = g_ptr_array_index(dir_content, i);
        const char *filepath = g_build_filename(path_current, file->path, NULL);
        GdkPixbuf *pix = NULL;

        if (strcmp(filter, "") != 0 && !g_str_match_string(filter, file->name, FALSE))
        {
            continue;
        }

        switch (file->type)
        {
        case BROWSER_FILE_T_TEXTURE:
            pix = gdk_pixbuf_new_from_file_at_scale(filepath, 64, 64, TRUE, NULL);
            break;
        }

        if (pix != NULL)
        {
            browserViewContentAppend(store, file->name, pix);
        }
    }
}

/*
 * Name: browserViewContentAppend
 * Private
 * Params: (GListStore *store, const char *name, const GdkPixbuf *image)
 * Return: void
 * Desc: Agregamos nuevos elementos al BrowserViewContent
 */
void browserViewContentAppend(GListStore *store, const char *name, const GdkPixbuf *image)
{
    g_list_store_append(store, browser_view_new(name, image));
}

/*
 * Name: browserViewContentClear
 * Private
 * Params: (GListStore *store)
 * Return: void
 * Desc: Limpiamos la lista de BrowserViewContent
 */
void browserViewContentClear(GListStore *store)
{
    g_list_store_remove_all(store);
}