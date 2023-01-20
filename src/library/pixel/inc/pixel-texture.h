#ifndef _PIXEL_TEXTURE_H
#define _PIXEL_TEXTURE_H
#include <stdio.h>
#include "pixel.h"

typedef struct pixel_texture_t
{
    unsigned int id;
    int width;
    int height;
} pixel_texture_t;

pixel_texture_t pixel_texture_load_file(const char *filename);

void pixel_texture_free(pixel_texture_t texture);

#endif
