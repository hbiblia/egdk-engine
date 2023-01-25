#ifndef PIXEL_COMPONENT_H
#define PIXEL_COMPONENT_H
#include "pixel.h"
#include "pixel-struct.h"
#include "pixel-ecs.h"

typedef enum
{
    COMPONENT_ID_COLOR_T,
    COMPONENT_ID_TEXTURE_T,
    COMPONENT_ID_RECT_T,
    COMPONENT_ID_VEC2_T,
    COMPONENT_ID_VEC3_T,
    COMPONENT_ID_VEC4_T,
    COMPONENT_ID_ENTITY_T,
    COMPONENT_ID_SPRITE_T,
    COMPONENT_ID_SPRITE_TYPE_ENUM_T,
    COMPONENTS_ID
} pEcsComponent_EnumId;

#define pEcsComponent_Declare()                     \
    ECS_COMPONENT_DECLARE(ComponentSpriteTypeEnum); \
    ECS_COMPONENT_DECLARE(color_t);                 \
    ECS_COMPONENT_DECLARE(texture_t);               \
    ECS_COMPONENT_DECLARE(rect_t);                  \
    ECS_COMPONENT_DECLARE(vec4_t);                  \
    ECS_COMPONENT_DECLARE(vec3_t);                  \
    ECS_COMPONENT_DECLARE(vec2_t);                  \
    ECS_COMPONENT_DECLARE(ComponentEntity);         \
    ECS_COMPONENT_DECLARE(ComponentSprite);

#define pEcsComponent_Define()                                   \
    ECS_COMPONENT_DEFINE(pEcs_World(), ComponentSpriteTypeEnum); \
    ECS_COMPONENT_DEFINE(pEcs_World(), color_t);                 \
    ECS_COMPONENT_DEFINE(pEcs_World(), texture_t);               \
    ECS_COMPONENT_DEFINE(pEcs_World(), rect_t);                  \
    ECS_COMPONENT_DEFINE(pEcs_World(), vec4_t);                  \
    ECS_COMPONENT_DEFINE(pEcs_World(), vec3_t);                  \
    ECS_COMPONENT_DEFINE(pEcs_World(), vec2_t);                  \
    ECS_COMPONENT_DEFINE(pEcs_World(), ComponentEntity);         \
    ECS_COMPONENT_DEFINE(pEcs_World(), ComponentSprite);

#define pEcsComponent_Register()                          \
    ECS_COMPONENT(pEcs_World(), ComponentSpriteTypeEnum); \
    ECS_COMPONENT(pEcs_World(), color_t);                 \
    ECS_COMPONENT(pEcs_World(), texture_t);               \
    ECS_COMPONENT(pEcs_World(), vec2_t);                  \
    ECS_COMPONENT(pEcs_World(), vec3_t);                  \
    ECS_COMPONENT(pEcs_World(), vec4_t);                  \
    ECS_COMPONENT(pEcs_World(), rect_t);                  \
    ECS_COMPONENT(pEcs_World(), ComponentEntity);         \
    ECS_COMPONENT(pEcs_World(), ComponentSprite);

void pEcsComponent_Init(ecs_world_t *world);
ecs_entity_t pEcsComponent_GetId(pEcsComponent_EnumId id);

#endif // PIXEL_COMPONENT_H