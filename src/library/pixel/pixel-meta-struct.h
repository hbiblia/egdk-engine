#ifndef PIXEL_META_STRUCT_H
#define PIXEL_META_STRUCT_H
#include <stdio.h>
#include "pixel/pixel-struct.h"
#include "pixel/pixel-ecs.h"

#define meta_struct_id(id) pMetaStruct_GetID(meta_##id)
#define component_id(id) pComponent_GetID(meta_##id)

typedef enum
{
    meta_vec2_t,
    meta_texture_t,
    meta_color_t,
    meta_rect_t,
    meta_sprite_t,
    meta_entity_info_t,
    meta_struct_lasts
} pMetaStructIDEnum;

void pEscMetaStruct_Init(ecs_world_t *world);

ecs_entity_t pMetaStruct_GetID(pMetaStructIDEnum id);
ecs_entity_t pComponent_GetID(pMetaStructIDEnum id);

#endif // PIXEL_META_STRUCT_H