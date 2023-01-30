#include "pixel/pixel-meta-struct.h"

static ecs_entity_t component_ids[meta_struct_lasts];
static ecs_entity_t meta_struct_ids[meta_struct_lasts];

void pEscMetaStruct_Init(ecs_world_t *world)
{
    component_ids[meta_vec2_t] = ecs_component_init(world, &(ecs_component_desc_t){
        .entity = ecs_entity(world, {.name = "vec2_t"}),
        .type.size = ECS_SIZEOF(vec2_t),
        .type.alignment = ECS_ALIGNOF(vec2_t)
    });

    meta_struct_ids[meta_vec2_t] = ecs_struct(world, {
        .entity = component_id(vec2_t),
        .members = {
            {.name = "x", .type = ecs_id(ecs_f32_t)},
            {.name = "y", .type = ecs_id(ecs_f32_t)},
        }
    });

    component_ids[meta_color_t] = ecs_component_init(world, &(ecs_component_desc_t){
        .entity = ecs_entity(world, {.name = "color_t"}),
        .type.size = ECS_SIZEOF(color_t),
        .type.alignment = ECS_ALIGNOF(color_t)
    });

    meta_struct_ids[meta_color_t] = ecs_struct(world, {
        .entity = component_id(color_t),
        .members = {
            {.name = "r", .type = ecs_id(ecs_f32_t)},
            {.name = "g", .type = ecs_id(ecs_f32_t)},
            {.name = "b", .type = ecs_id(ecs_f32_t)},
            {.name = "a", .type = ecs_id(ecs_f32_t)},
        }
    });

    component_ids[meta_rect_t] = ecs_component_init(world, &(ecs_component_desc_t){
        .entity = ecs_entity(world, {.name = "rect_t"}),
        .type.size = ECS_SIZEOF(rect_t),
        .type.alignment = ECS_ALIGNOF(rect_t)
    });

    meta_struct_ids[meta_rect_t] = ecs_struct(world, {
        .entity = component_id(rect_t),
        .members = {
            {.name = "x", .type = ecs_id(ecs_f32_t)},
            {.name = "y", .type = ecs_id(ecs_f32_t)},
            {.name = "w", .type = ecs_id(ecs_u16_t)},
            {.name = "h", .type = ecs_id(ecs_u16_t)},
        }
    });

    component_ids[meta_texture_t] = ecs_component_init(world, &(ecs_component_desc_t){
        .entity = ecs_entity(world, {.name = "texture_t"}),
        .type.size = ECS_SIZEOF(texture_t),
        .type.alignment = ECS_ALIGNOF(texture_t)
    });

    meta_struct_ids[meta_texture_t] = ecs_struct(world, {
        .entity = component_id(texture_t),
        .members = {
            {.name = "id", .type = ecs_id(ecs_u8_t)},
            {.name = "width", .type = ecs_id(ecs_u8_t)},
            {.name = "height", .type = ecs_id(ecs_u8_t)},
        }
    });

    component_ids[meta_sprite_t] = ecs_component_init(world, &(ecs_component_desc_t){
        .entity = ecs_entity(world, {.name = "ComponentSprite"}),
        .type.size = ECS_SIZEOF(sprite_t),
        .type.alignment = ECS_ALIGNOF(sprite_t)
    });

    meta_struct_ids[meta_sprite_t] = ecs_struct(world, {
        .entity = component_id(sprite_t),
        .members = {
            {.name = "Texture", .type = component_id(texture_t)},
            {.name = "Color", .type = component_id(color_t)},
            {.name = "Opacity", .type = ecs_id(ecs_f32_t)},
            {.name = "FlipX", .type = ecs_id(ecs_bool_t)},
            {.name = "FlipY", .type = ecs_id(ecs_bool_t)},
            {.name = "Hframes", .type = ecs_id(ecs_i32_t)},
            {.name = "Vframes", .type = ecs_id(ecs_i32_t)},
            {.name = "frame", .type = ecs_id(ecs_i32_t)},
        }
    });

    component_ids[meta_entity_info_t] = ecs_component_init(world, &(ecs_component_desc_t){
        .entity = ecs_entity(world, {.name = "ComponentEntity"}),
        .type.size = ECS_SIZEOF(entity_info_t),
        .type.alignment = ECS_ALIGNOF(entity_info_t)
    });

    meta_struct_ids[meta_entity_info_t] = ecs_struct(world, {
        .entity = component_id(entity_info_t),
        .members = {
            {.name = "enable", .type = ecs_id(ecs_bool_t)},
            {.name = "name", .type = ecs_id(ecs_string_t)},
            {.name = "position", .type = component_id(vec2_t)},
            {.name = "scale", .type = component_id(vec2_t)},
            {.name = "rotation", .type = ecs_id(ecs_f32_t)},
        }
    });
}

ecs_entity_t pMetaStruct_GetID(pMetaStructIDEnum id)
{
    return meta_struct_ids[id];
}

ecs_entity_t pComponent_GetID(pMetaStructIDEnum id)
{
    return component_ids[id];
}