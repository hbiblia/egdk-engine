#ifndef PIXEL_STRUCT_H
#define PIXEL_STRUCT_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

typedef struct
{
    float x;
    float y;
} vec2_t;

typedef struct
{
    float r;
    float g;
    float b;
    float a;
} color_t;

typedef struct
{
    float x;
    float y;
    float w;
    float h;
} rect_t;

typedef struct
{
    unsigned int id;
    int width;
    int height;
} texture_t;

typedef struct
{
    vec2_t position;
    vec2_t scale;
    float rotation;
    vec2_t pivot;
    rect_t box;
} transform_t;

typedef struct
{
    texture_t texture;
    color_t color;
    float opacity;
    bool flipX;
    bool flipY;
    // config spriteSheet
    uint32_t Hframes;
    uint32_t Vframes;
    uint32_t frame;
    // hide params
    rect_t dest_rect;
    rect_t src_rect;
} sprite_t;

typedef struct
{
    int n;
}animated_t;

typedef struct
{
    bool enable;
    char *name;
    vec2_t position;
    vec2_t scale;
    float rotation;
} entity_info_t;

#endif // PIXEL_STRUCT_H