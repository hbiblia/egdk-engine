#include <stdlib.h>
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
        printf("Enable: %d\n", s[i].enable);
    }
}

void pComponent_EntityInit(ecs_world_t *world)
{
    ecs_observer(world, {.filter = {
                             .terms = {{.id = component_id(entity_info_t)}},
                         },
                         .events = {EcsOnSet},
                         .callback = pComponent_EntityOnSet});
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
    s->Hframes = 1;
    s->Vframes = 1;
    s->frame = 0;
}

void pComponent_SpriteOnStore(ecs_iter_t *it)
{
    sprite_t *s = ecs_field(it, sprite_t, 1);
    entity_info_t *entity = ecs_field(it, entity_info_t, 2);
    for (int i = 0; i < it->count; i++)
    {
        if (entity->enable == true && s[i].texture.id > 0)
        {
            color_t tint = s[i].color;

            int textureWidth = s[i].texture.width;
            int textureHeight = s[i].texture.height;

            rect_t dst = (rect_t){0, 0, (float)textureWidth, (float)textureHeight};
            rect_t src = dst;

            int frameWidth = (textureWidth / s[i].Hframes);
            int frameHeight = (textureHeight / s[i].Vframes);

            // color y opacity
            tint.a = s[i].opacity;
            // Clip
            if (frameWidth != textureWidth || frameHeight != textureHeight)
            {
                dst.w = src.w = frameWidth;
                dst.h = src.h = frameHeight;
                src.x = (float)(s[i].frame % (int)(textureWidth / frameWidth)) * frameWidth;
                src.y = (float)(s[i].frame / (textureWidth / frameHeight)) * frameHeight;
            }
            // flip source
            src.w = s[i].flipX ? (src.w * -1) : src.w;
            src.h = s[i].flipY ? (src.h * -1) : src.h;

            pGfx_DrawTexture(s[i].texture, src, dst, tint);
        }
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
