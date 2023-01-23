#ifndef PIXEL_GFX_H
#define PIXEL_GFX_H
#include <stdio.h>
#include <stdint.h>
#include "pixel-math.h"

#define RED         ((color_t){255, 0, 0, 255})
#define GREEN       ((color_t){0, 255, 0, 255})
#define BLUE        ((color_t){0, 0, 255, 255})
#define BLACK       ((color_t){0, 0, 0, 255})

void pGfx_Init();
void pGfx_Shutdown(void);
void pGfx_BeginFrame(int width, int height);
void pGfx_EndFrame(void);
void pGfx_Viewport(int x, int y, int width, int height);
void pGfx_Project(float left, float right, float top, float bottom);
void pGfx_ClearColor(color_t color);
void pGfx_SetColor(color_t color);
void pGfx_SetRotate(float theta, float x, float y);
void pGfx_SetScale(float sx, float sy, float x, float y);
void pGfx_SetTranslate(float x, float y);

// Transform make
void pGfx_PushTransform(void);
void pGfx_PopTransform(void);

// Shape Draw
void pGfx_DrawFilledRect(float x, float y, float w, float h);
void pGfx_DrawCheckboard(int width, int height, int screen_width, int screen_height);

#endif
