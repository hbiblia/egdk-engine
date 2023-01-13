#include "rshape.h"
#include "renderer.h"

void rshape_draw_rectangle(rshape_desc *rect)
{
    renderer_transform_begin(rect->t);
    {
        float w = rect->w;
        float h = rect->h;
        rcolor color = rect->color;

        renderer_begin_quads();
        {
            renderer_v2f_c3b(-w, -h, color.r, color.g, color.b);
            renderer_v2f_c3b(+w, -h, color.r, color.g, color.b);
            renderer_v2f_c3b(+w, +h, color.r, color.g, color.b);
            renderer_v2f_c3b(-w, +h, color.r, color.g, color.b);
        }
        renderer_end();
    }
    renderer_transform_end();
}