#include "pixel-gfx.h"
#include "pixel-gui.h"
#include "pixel-window.h"
#include "pixel.h"

#include "sokol/sokol_time.h"
#include "sokol/sokol_gfx.h"
#include "sokol/sokol_gp.h"

void pGfx_Init()
{
    sgp_setup(&(sgp_desc){0});
}

void pGfx_Shutdown(void)
{
    sgp_shutdown();
}

void pGfx_BeginFrame(int width, int height)
{
    sgp_begin(width, height);
}

void pGfx_EndFrame(void)
{
    sgp_flush();
    sgp_end();
}

void pGfx_Viewport(int x, int y, int width, int height)
{
    sgp_viewport(x, y, width, height);
}

void pGfx_Project(float left, float right, float top, float bottom)
{
    sgp_project(left, right, top, bottom);
}

void pGfx_ClearColor(color_t color)
{
    pGfx_SetColor(color);
    sgp_clear();
}

void pGfx_SetColor(color_t color)
{
    float r = (float)color.r / 255;
    float g = (float)color.g / 255;
    float b = (float)color.b / 255;
    float a = (float)color.a / 255;
    sgp_set_color(r, g, b, a);
}

void pGfx_SetRotate(float theta, float x, float y)
{
    sgp_rotate_at(theta, x, y);
}

void pGfx_SetScale(float sx, float sy, float x, float y)
{
    sgp_scale_at(sx, sy, x, y);
}

void pGfx_SetTranslate(float x, float y)
{
    sgp_translate(x, y);
}

// Transform make
void pGfx_PushTransform(void)
{
    sgp_push_transform();
}

void pGfx_PopTransform(void)
{
    sgp_pop_transform();
}

// Draw Shape
void pGfx_DrawFilledRect(float x, float y, float w, float h)
{
    sgp_draw_filled_rect(x, y, w, h);
}

void pGfx_DrawCheckboard(int width, int height, int screen_width, int screen_height)
{
    pGfx_SetColor((color_t){25, 25, 25, 255});
    sgp_clear();
    pGfx_SetColor((color_t){35, 35, 35, 255});

    for (int y = 0; y < screen_height / height + 1; y++)
        for (int x = 0; x < screen_width / width + 1; x++)
            if ((x + y) % 2 == 0)
                pGfx_DrawFilledRect(x * width, y * height, width, height);
    sgp_reset_color();
}
