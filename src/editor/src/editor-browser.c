#include "editor-browser.h"
#include "file_fn.h"
#include "path_fn.h"
#include "pixel-texture.h"
#include "pixel-resource.h"
#include <glib.h>

gint browser_view_list_func_sorty(gconstpointer a, gconstpointer b)
{
    const FileDirFile *file1 = *((FileDirFile **)a);
    const FileDirFile *file2 = *((FileDirFile **)b);

    return file1->type > FILE_FOLDER;
}

GPtrArray *browser_list_dir_content(const char *path)
{
    GPtrArray *dirCurrentFolder = NULL;
    dirCurrentFolder = FileReaddir(path);

    g_ptr_array_sort(dirCurrentFolder, browser_view_list_func_sorty);

    for (int i = 0; i < dirCurrentFolder->len; i++)
    {
        FileDirFile *file = g_ptr_array_index(dirCurrentFolder, i);
        if (file->type == FILE_TEXTURE)
        {
            pixel_texture_t t = pixel_texture_load_file(PathBuild(file->path, file->filename, NULL));
            file->image_id = t.id;
        }
        else if (file->type == FILE_FOLDER)
        {
            file->image_id = pixel_resource_get_icon_id_default(RESOUCE_ICON_FOLDER);
        }
    }

    return dirCurrentFolder;
}

void browser_home_path(void)
{
    prChangeCurrentContentFolder(prGetPath(RESOURCE_PATH_ASSETS_DEFAULT), NULL);
}

void browser_move_back_path(void)
{
    const char *path_current = prGetPath(RESOURCE_PATH_ASSETS_CURRENT);
    const char *default_path = prGetPath(RESOURCE_PATH_ASSETS_DEFAULT);

    if (strcmp(path_current, default_path) == 0)
        return;

    prChangeCurrentContentFolder(g_dirname(path_current), NULL);
}