#ifndef _PIXEL_RESOURCE_H
#define _PIXEL_RESOURCE_H
#include <stdio.h>
#include "pixel.h"

typedef enum
{
    RESOURCE_PATH_ASSETS_ENGINE,
    RESOURCE_PATH_PROJECT,
    RESOURCE_PATH_ASSETS_DEFAULT,
    RESOURCE_PATH_ASSETS_CURRENT,
    RESOURCE_PATH_CONFIG,
    RESOURCE_LAST
} pixel_resource_paths;

typedef enum
{
    RESOUCE_ICON_JSON = 0,
    RESOUCE_ICON_LEVEL,
    RESOUCE_ICON_SCRIPT,
    RESOUCE_ICON_FOLDER,
    RESOUCE_ICON_ANIM,
    RESOUCE_ICON_ACTOR,
    RESOUCE_ICON_COMPONENT,
    RESOUCE_ICONS
} pixel_resource_icons;

void pixel_resource_init(void);
void pixel_resource_project_init(const char *path);
const char *pixel_resource_get_path(pixel_resource_paths path);
unsigned int pixel_resource_get_icon_id_default(pixel_resource_icons icon);

#endif
