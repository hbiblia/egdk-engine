#include "pixel-transform.h"
#include "pixel-gfx.h"

transform_t transform_make(void)
{
    transform_t t = {0};

    t.position = (vec2_t){0.0f, 0.0f};
    t.scale = (vec2_t){1.0f, 1.0f};
    t.pivot = (vec2_t){0.0f, 0.0f};
    t.rotation = 0.0f;

    return t;
}

void transform_begin_make(transform_t t)
{
    sgp_push_transform();
    pGfx_SetTranslate(t.position.x, t.position.y);
    pGfx_SetScale(t.scale.x, t.scale.y, t.pivot.x, t.pivot.y);
    pGfx_SetRotate(t.rotation, t.pivot.x, t.pivot.y);
}

void transform_end()
{
    sgp_pop_transform();
}
