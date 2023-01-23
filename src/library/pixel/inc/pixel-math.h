#ifndef _PIXEL_MATH_H
#define _PIXEL_MATH_H
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

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

#endif // _PIXEL_MATH_H
