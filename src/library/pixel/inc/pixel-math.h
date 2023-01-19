#ifndef RMATH_H
#define RMATH_H
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
} rcolor;

typedef struct
{
    float x;
    float y;
} rvect2;

typedef struct
{
    float x;
    float y;
    float z;
} rvect3;

typedef struct
{
    float x;
    float y;
    float z;
    float w;
} rvect4;

typedef struct
{
    float x;
    float y;
    float w;
    float h;
} rrect;

typedef struct
{
    rvect3 position;
    rvect3 scale;
    rvect3 rotation;
    rvect2 pivot;
    // bounding box
    rvect4 box;
} rtransform;

#endif