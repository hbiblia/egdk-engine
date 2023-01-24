#pragma once

#ifndef _PIXEL_H
#define _PIXEL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include "cimgui/cimgui.h"

typedef struct
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
} color_t;

typedef struct
{
    float x;
    float y;
} vec2_t;

typedef struct
{
    float x;
    float y;
    float z;
} vec3_t;

typedef struct
{
    float x;
    float y;
    float z;
    float w;
} vec4_t;

typedef struct
{
    float x;
    float y;
    uint16_t w;
    uint16_t h;
} rect_t;

typedef struct
{
    vec2_t position;
    vec2_t scale;
    float rotation;
    vec2_t pivot;
    rect_t box;
} transform_t;

typedef struct pixel_event_t
{
    void *event;
} pixel_event_t;

typedef struct pixel_window_desc
{
    void (*init_fn)(void);                   //
    void (*draw_fn)(float dt);               //
    void (*event_fn)(const pixel_event_t *); //
    void (*shutdown_fn)(void);               //

    const char *title; // Titulo de la ventana
    int width;
    int height;
} pixel_window_desc;

typedef struct pixel_texture_t
{
    unsigned int id;
    int width;
    int height;
} pixel_texture_t;

typedef enum
{
    RESOURCE_PATH_ASSETS_ENGINE,
    RESOURCE_PATH_PROJECT,
    RESOURCE_PATH_ASSETS_DEFAULT,
    RESOURCE_PATH_ASSETS_CURRENT,
    RESOURCE_PATH_CONFIG,
    RESOURCE_LAST
} pixel_resource_paths;

typedef enum
{
    RESOUCE_ICON_JSON = 0,
    RESOUCE_ICON_LEVEL,
    RESOUCE_ICON_SCRIPT,
    RESOUCE_ICON_FOLDER,
    RESOUCE_ICON_ANIM,
    RESOUCE_ICON_ACTOR,
    RESOUCE_ICON_COMPONENT,
    RESOUCE_ICONS
} pixel_resource_icons;

#define RED         ((color_t){255, 0, 0, 255})
#define GREEN       ((color_t){0, 255, 0, 255})
#define BLUE        ((color_t){0, 0, 255, 255})
#define BLACK       ((color_t){0, 0, 0, 255})

/***
 *
 *  struct PixelBase
 *
 *  PixelGui
 *
 */

#define MAX_INPUT_TEXT 32

#define pgInputText(label, buffer) igInputText(label, buffer, MAX_INPUT_TEXT, 0, NULL, NULL)
#define pgButton(label, width, height) igButton(label, (ImVec2){width, height})
#define pgButtonImage(id, texture, size_w, size_h) igImageButton(id, (void *)texture, (const ImVec2){size_w, size_h}, (ImVec2){0, 0}, (ImVec2){1, 1}, (ImVec4){0, 0, 0, 0}, (ImVec4){1, 1, 1, 1.0f})
#define pgSeparator() igSeparator()
#define pgBeginViewList(id, columnCount) igBeginTable(id, columnCount, ImGuiTableFlags_ScrollY, (ImVec2){0, 0}, 0.0f)
#define pgEndViewList() igEndTable()
#define pgBeginChildViewList(id) \
    igTableNextColumn();         \
    igPushID_Str(id)
#define pgEndChildViewList() igPopID()
#define pgTextWrap(...) igTextWrapped(__VA_ARGS__)

#define pgStyleColor(id, r, g, b, a) igPushStyleColor_Vec4(id, (ImVec4){r, g, b, a})
#define pgStyleColorClear igPopStyleColor

/***
 *
 *  struct PixelBase
 *
 *  PixelWindow
 *
 */

void pWindow_Main(const pixel_window_desc *desc);
int pWindow_GetWidth(void);
int pWindow_GetHeight(void);
double pWindow_DeltaTime(void);
uint64_t pWindow_FrameCount(void);
float pWindow_DpiScale(void);

/***
 *
 *  struct PixelBase
 *
 *  PixelGfx
 *
 */

void pGfx_Init(void);
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
void pGfx_DrawFilledRect(float x, float y, float w, float h);
void pGfx_DrawCheckboard(int width, int height, int screen_width, int screen_height);

/***
 *
 *  struct PixelBase
 *
 *  PixelTransform
 *
 */

void pTransform_BeginMake(transform_t t);
void pTransform_End(void);

/***
 *
 *  struct PixelBase
 *
 *  PixelTexture
 *
 */

pixel_texture_t pTexture_LoadFile(const char *filename);
void pTexture_Free(pixel_texture_t texture);

/***
 *
 *  struct PixelBase
 *
 *  PixelResource
 *
 */

void pResource_Init(void);
void pResource_ProjectInit(const char *path);
void pResource_ChangeCurrentContentFolder(const char *path, const char *filename);
bool pResource_CurrentContentFolderHasChanges(void);
const char *pResource_GetPath(pixel_resource_paths path);
unsigned int pResource_GetIconId(pixel_resource_icons icon);

#endif