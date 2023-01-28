#include "pixel-components.h"
#include "pixel-struct.h"
#include "pixel-meta-struct.h"
#include "pixel-ecs.h"
#include "pixel.h"

/***
 *
 * PIXEL-COMPONENT-ENTITY
 *
 *
 */

void pComponent_EntityOnSet(ecs_iter_t *it)
{
    entity_info_t *s = ecs_field(it, entity_info_t, 1);
    for (int i = 0; i < it->count; i++)
    {
        pEcs_EntitySetEnable(it->entities[i], s[i].enable);
        printf("Enable: %d\n",s[i].enable);
    }
}

void pComponent_EntityInit(ecs_world_t *world)
{
    ecs_observer(world, {
        .filter = {
            .terms = {{.id = component_id(entity_info_t)}},
        },
        .events = {EcsOnSet},
        .callback = pComponent_EntityOnSet
    });
}

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
        float sw = s[i].src_rect.w == 0 ? s[i].texture.width : s[i].src_rect.w;
        float sh = s[i].src_rect.h == 0 ? s[i].texture.height : s[i].src_rect.h;

        float dw = s[i].dest_rect.w == 0 ? s[i].texture.width : s[i].dest_rect.w;
        float dh = s[i].dest_rect.h == 0 ? s[i].texture.height : s[i].dest_rect.h;

        // color y opacity
        color_t tint    = s[i].color;
        tint.a = s[i].opacity;

        // flip
        sw = s[i].flipX ? sw * -1 : sw;
        sh = s[i].flipY ? sh * -1 : sh;

        // offset
        float offsetX   = s[i].dest_rect.x;
        float offsetY   = s[i].dest_rect.y;

        // clip
        float clipX     = s[i].src_rect.x;
        float clipY     = s[i].src_rect.y;

        rect_t source   = (rect_t){.x = clipX, .y = clipY, .w = sw, .h = sh};
        rect_t dest     = (rect_t){.x = offsetX, .y = offsetY, .w = dw, .h = dh};

        pGfx_DrawTexture(s[i].texture, source, dest, tint);
    }
}

void pComponent_SpriteInit(ecs_world_t *world)
{
    ecs_observer(world, {.filter = {
                             .terms = {{.id = component_id(sprite_t)}},
                         },
                         .events = {EcsOnAdd},
                         .callback = pComponent_SpriteOnAdd});

    ecs_system(world, {.entity = ecs_entity(world, {.name = "pComponent_SpriteOnStore",
                                                    .add = {ecs_dependson(EcsOnStore)}}),
                       .query.filter.terms = {
                           {.id = component_id(sprite_t)},
                           {.id = component_id(entity_info_t), .inout = EcsIn},
                       },
                       .callback = pComponent_SpriteOnStore});
}

/***
 *
 * PIXEL-COMPONENT-BOUNDING-BOX
 *
 *
 */

/***
 *
 * PIXEL-COMPONENT
 *
 *
 */

void pEcsComponent_Init(void)
{
    ecs_world_t *world = pEcs_World();

    pComponent_EntityInit(world);
    pComponent_SpriteInit(world);
}
