#ifndef _PIXEL_TRANSFORM_H
#define _PIXEL_TRANSFORM_H
#include <stdio.h>
#include "pixel-math.h"

transform_t transform_make(void);
void transform_begin_make(transform_t t);
void transform_end();

#endif