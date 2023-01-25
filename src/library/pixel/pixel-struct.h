#ifndef PIXEL_STRUCT_H
#define PIXEL_STRUCT_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

typedef enum
{
    Simple,
    Animated
} ComponentSpriteTypeEnum;

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

typedef struct
{
    unsigned int id;
    int width;
    int height;
} texture_t;

typedef struct
{
    bool enable;
    char *name;
    vec2_t position;
    vec2_t scale;
    float rotation;
    vec2_t pivot;
} ComponentEntity;

typedef struct
{
    ComponentSpriteTypeEnum type;
    texture_t texture;
    int frame;
    float opacity;
    bool flipX;
    bool flipY;
} ComponentSprite;

#endif // PIXEL_STRUCT_H