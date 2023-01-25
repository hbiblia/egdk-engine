#include "pixel-component.h"
#include "pixel-ecs.h"

static ecs_entity_t components_r[COMPONENTS_ID];

void pEcsComponent_Init(ecs_world_t *world)
{
    pEcsComponent_Register();
    
    components_r[COMPONENT_ID_SPRITE_TYPE_ENUM_T] = ecs_enum(world, {
        .entity = ecs_id(ComponentSpriteTypeEnum),
        .constants = {
            {.name = "Simple", .value = Simple},
            {.name = "Animated", .value = Animated},
        }
    });

   components_r[COMPONENT_ID_VEC2_T] = ecs_struct(world, {
        .entity = ecs_id(vec2_t),
        .members = {
            {.name = "x", .type = ecs_id(ecs_f32_t)},
            {.name = "y", .type = ecs_id(ecs_f32_t)},
        }
    });

    components_r[COMPONENT_ID_VEC3_T] = ecs_struct(world, {
        .entity = ecs_id(vec3_t),
        .members = {
            {.name = "x", .type = ecs_id(ecs_f32_t)},
            {.name = "y", .type = ecs_id(ecs_f32_t)},
            {.name = "z", .type = ecs_id(ecs_f32_t)},
        }
    });

    components_r[COMPONENT_ID_VEC4_T] = ecs_struct(world, {
        .entity = ecs_id(vec4_t),
        .members = {
            {.name = "x", .type = ecs_id(ecs_f32_t)},
            {.name = "y", .type = ecs_id(ecs_f32_t)},
            {.name = "z", .type = ecs_id(ecs_f32_t)},
            {.name = "w", .type = ecs_id(ecs_f32_t)},
        }
    });

    components_r[COMPONENT_ID_RECT_T] = ecs_struct(world, {
        .entity = ecs_id(rect_t),
        .members = {
            {.name = "x", .type = ecs_id(ecs_f32_t)},
            {.name = "y", .type = ecs_id(ecs_f32_t)},
            {.name = "w", .type = ecs_id(ecs_u16_t)},
            {.name = "h", .type = ecs_id(ecs_u16_t)},
        }
    });

    components_r[COMPONENT_ID_COLOR_T] = ecs_struct(world, {
        .entity = ecs_id(color_t),
        .members = {
            {.name = "r", .type = ecs_id(ecs_u8_t)},
            {.name = "g", .type = ecs_id(ecs_u8_t)},
            {.name = "b", .type = ecs_id(ecs_u8_t)},
            {.name = "a", .type = ecs_id(ecs_u8_t)},
        }
    });

    components_r[COMPONENT_ID_TEXTURE_T] = ecs_struct(world, {
        .entity = ecs_id(texture_t),
        .members = {
            {.name = "id", .type = ecs_id(ecs_u8_t)},
            {.name = "width", .type = ecs_id(ecs_u8_t)},
            {.name = "height", .type = ecs_id(ecs_u8_t)},
        }
    });

    components_r[COMPONENT_ID_SPRITE_T] = ecs_struct(world, {
        .entity = ecs_id(ComponentSprite),
        .members = {
            {.name = "Type", .type = ecs_id(ComponentSpriteTypeEnum)},
            {.name = "Texture", .type = ecs_id(texture_t)},
            {.name = "Frame", .type = ecs_id(ecs_u8_t)},
            {.name = "Opacity", .type = ecs_id(ecs_f32_t)},
            {.name = "Frame", .type = ecs_id(ecs_f32_t)},
            {.name = "FlipX", .type = ecs_id(ecs_bool_t)},
            {.name = "FlipY", .type = ecs_id(ecs_bool_t)},
        }
    });

    components_r[COMPONENT_ID_ENTITY_T] = ecs_struct(world, {
        .entity = ecs_id(ComponentEntity),
        .members = {
            {.name = "Enable", .type = ecs_id(ecs_bool_t)},
            {.name = "Name", .type = ecs_id(ecs_string_t)},
            {.name = "Position", .type = ecs_id(vec2_t)},
            {.name = "Scale", .type = ecs_id(vec2_t)},
            {.name = "Rotation", .type = ecs_id(ecs_f32_t)},
            // {.name = "pivot", .type = ecs_id(vec2_t)},
        }
    });
}

ecs_entity_t pEcsComponent_GetId(pEcsComponent_EnumId id)
{
    return components_r[id];
}