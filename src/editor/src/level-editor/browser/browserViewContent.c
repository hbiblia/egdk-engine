
#include "browserViewContent.h"
#include "browserContent.h"
#include "browserViewFileType.h"

const gchar *path_current = "";

typedef struct
{
    gchar *name;
    gchar *path;
    BrowserFileType type;
} BrowserViewContentFile;

/*
 * Name: browserViewContentStringReplace
 * Private
 * Params: (const char *str, const char *find, const char *replace)
 * Return: char *
 * Desc: Remplazamos un string por otro string
 */
char *browserViewContentStringReplace(const char *str, const char *find, const char *replace)
{
    GString *gstr = g_string_new(str);
    g_string_replace(gstr, find, replace, 0);
    return g_string_free(gstr, false);
}

/*
 * Name: browserViewContentPathNormalize
 * Private
 * Params: (const char *path)
 * Return: char *
 * Desc: Normalizamos el path
 */
char *browserViewContentPathNormalize(const char *path)
{
    char *new_path = NULL;
#if defined(_WIN32)
    new_path = browserViewContentStringReplace(path, "/", "\\");
#else
    new_path = browserViewContentStringReplace(path, "\\", "/");
#endif
    return new_path;
}

/*
 * Name: browserViewContentFileGetExt
 * Private
 * Params: (const gchar *filename)
 * Return: const gchar *
 * Desc: Obtenemos la ext de un archivo
 */
const gchar *browserViewContentFileGetExt(const gchar *filename)
{
    const gchar *dot = strrchr(filename, '.');
    return (!dot || dot == filename) ? "" : (dot + 1);
}

/*
 * Name: browserViewContentFileIsExt
 * Private
 * Params: (const gchar *filename)
 * Return: gboolean
 * Desc: Comprobamos si un filename tiene la ext
 */
gboolean browserViewContentFileIsExt(const gchar *filename, const gchar *ext)
{
    const gchar *ext_o = browserViewContentFileGetExt(filename);
    return strcmp(ext_o, ext) == 0 ? TRUE : FALSE;
}

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
        file->path = browserViewContentPathNormalize(g_build_filename(project_path, filename, NULL));

        if (g_file_test(file->path, G_FILE_TEST_IS_DIR))
        {
            file->type = BROWSER_FILE_T_FOLDER;
        }
        else if (browserViewContentFileIsExt(file->path, "jpg") || browserViewContentFileIsExt(file->path, "png"))
        {
            file->type = BROWSER_FILE_T_TEXTURE;
        }
        else if (browserViewContentFileIsExt(file->path, "lua"))
        {
            file->type = BROWSER_FILE_T_LUA;
        }
        else if (browserViewContentFileIsExt(file->path, "tiled"))
        {
            file->type = BROWSER_FILE_T_TILED;
        }
        else if (browserViewContentFileIsExt(file->path, "json"))
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