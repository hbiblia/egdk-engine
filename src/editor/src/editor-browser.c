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

    FileReaddirFree(dirCurrentFolder);
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