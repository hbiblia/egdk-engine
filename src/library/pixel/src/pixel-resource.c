#include "pixel-resource.h"
#include "path_fn.h"
#include "string_fn.h"
#include "pixel-texture.h"

static char *path_resource[RESOURCE_LAST];
static pixel_texture_t icon_default[RESOUCE_ICONS];
static bool bpath_current_content_change = false;

void pixel_resource_init(void)
{
    printf("INFO: Resource Init\n");
    path_resource[RESOURCE_PATH_ASSETS_ENGINE] = PathBuild(PathPwd(), "resource", NULL);

    icon_default[RESOUCE_ICON_FOLDER] = pixel_texture_load_file(PathBuild(path_resource[RESOURCE_PATH_ASSETS_ENGINE], "textures", "folder.png", NULL));
}

void pixel_resource_project_init(const char *path)
{
    path_resource[RESOURCE_PATH_PROJECT] = PathNormalize(path);
    path_resource[RESOURCE_PATH_CONFIG] = PathBuild(path, "config", NULL);
    path_resource[RESOURCE_PATH_ASSETS_DEFAULT] = PathBuild(path, "Content", NULL);
    prChangeCurrentContentFolder(path_resource[RESOURCE_PATH_ASSETS_DEFAULT], NULL);
}

void prChangeCurrentContentFolder(const char *path, const char *filename)
{
    bpath_current_content_change = true;
    path_resource[RESOURCE_PATH_ASSETS_CURRENT] = PathBuild(path, filename, NULL);
}

bool prCurrentContentFolderHasChanges(void)
{
    bool r = bpath_current_content_change;
    bpath_current_content_change = false;
    return r;
}

const char *prGetPath(pixel_resource_paths path)
{
    return path_resource[path];
}

unsigned int pixel_resource_get_icon_id_default(pixel_resource_icons icon)
{
    return icon_default[icon].id;
}
