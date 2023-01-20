#include "pixel-resource.h"
#include "path_fn.h"
#include "string_fn.h"
#include "pixel-texture.h"

static char *path_resource[RESOURCE_LAST];
static pixel_texture_t icon_default[RESOUCE_ICONS];

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
    path_resource[RESOURCE_PATH_ASSETS_DEFAULT] = PathBuild(path, "resource", NULL);
    path_resource[RESOURCE_PATH_ASSETS_CURRENT] = StringDup(path_resource[RESOURCE_PATH_ASSETS_DEFAULT]);

}

const char *pixel_resource_get_path(pixel_resource_paths path)
{
    return path_resource[path];
}

unsigned int pixel_resource_get_icon_id_default(pixel_resource_icons icon)
{
    return icon_default[icon].id;
}
