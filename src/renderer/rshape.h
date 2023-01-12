#ifndef RSHAPE_H
#define RSHAPE_H
#include <stdio.h>
#include "rmath.h"

typedef struct
{
    float w;
    float h;
    rtransform t;
    rcolor color;
} rshape_desc;

void rshape_draw_rectangle(rshape_desc *rect);

#endif
