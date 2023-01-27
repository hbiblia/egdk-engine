#include "editor-browser.h"
#include "utility/file_fn.h"
#include "utility/path_fn.h"
#include "pixel/pixel.h"
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
            texture_t t = pTexture_LoadFile(PathBuild(file->path, file->filename, NULL));
            file->image_id = t.id;
        }
        else if (file->type == FILE_FOLDER)
        {
            file->image_id = pResource_GetIconId(RESOUCE_ICON_FOLDER);
        }
    }

    return dirCurrentFolder;
}

void browser_home_path(void)
{
    pResource_ChangeCurrentContentFolder(pResource_GetPath(RESOURCE_PATH_ASSETS_DEFAULT), NULL);
}

void browser_move_back_path(void)
{
    const char *path_current = pResource_GetPath(RESOURCE_PATH_ASSETS_CURRENT);
    const char *default_path = pResource_GetPath(RESOURCE_PATH_ASSETS_DEFAULT);

    if (strcmp(path_current, default_path) == 0)
        return;

    pResource_ChangeCurrentContentFolder(g_dirname(path_current), NULL);
}