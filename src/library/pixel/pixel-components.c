#include "pixel-components.h"
#include "pixel-struct.h"
#include "pixel-meta-struct.h"
#include "pixel-ecs.h"
#include "pixel.h"

/***
 *
 * PIXEL-COMPONENT-SPRITE
 *
 *
 */
void pComponent_SpriteOnAdd(ecs_iter_t *it)
{
    sprite_t *s = ecs_field(it, sprite_t, 1);
    s->color = ((color_t){1.0f, 1.0f, 1.0f, 1.0f});
    s->opacity = 1.0f;
}

void pComponent_SpriteOnStore(ecs_iter_t *it)
{
    sprite_t *s = ecs_field(it, sprite_t, 1);
    entity_info_t *entity = ecs_field(it, entity_info_t, 2);
    for (int i = 0; i < it->count; i++)
    {
        pGfx_SetColor(s->color);
        pGfx_DrawTexture(s[i].texture, (transform_t){.position = entity[i].position, .scale = entity[i].scale, .rotation = entity[i].rotation});
    }
}

void pComponent_SpriteInit(ecs_world_t *world)
{
    ecs_observer(world, {
        .filter = {
            .terms = {{.id = component_id(sprite_t)}},
        },
        .events = {EcsOnAdd},
        .callback = pComponent_SpriteOnAdd
    });

    ecs_system(world, {
        .entity = ecs_entity(world, {
            .name = "pComponent_SpriteOnStore",
            .add = { ecs_dependson(EcsOnStore) }
        }),
        .query.filter.terms = {
            {.id = component_id(sprite_t)},
            {.id = component_id(entity_info_t), .inout = EcsIn},
        },
        .callback = pComponent_SpriteOnStore
    });
}

/***
 *
 * PIXEL-COMPONENT
 *
 *
 */

void pEcsComponent_Init(void)
{
    ecs_world_t *world = pEcs_World();

    pComponent_SpriteInit(world);
}
