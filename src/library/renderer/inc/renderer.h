#ifndef RENDERER_H
#define RENDERER_H
#include <stdio.h>
#include <epoxy/gl.h>

#include "rmath.h"

void renderer_init(void);
void renderer_frame(void);
void renderer_resize(int width, int height);
void renderer_shutdown(void);
rvect2 renderer_get_size(void);

double renderer_delta_time(void);

void renderer_push_matrix(void);
void renderer_pop_matrix(void);
void renderer_begin_quads(void);
void renderer_end(void);
void renderer_defaults(void);
void renderer_pipeline_begin(void);
void renderer_pipeline_end(void);
void renderer_draw(void);
void renderer_projection(void);

void renderer_v2f_c3b(float x, float y, uint8_t r, uint8_t g, uint8_t b);

void renderer_scissor_rect(int x, int y, int w, int h);
void renderer_ortho(float l, float r, float b, float t, float n, float f);
void renderer_viewport(float x, float y, float width, float height);

void renderer_transform_begin(rtransform t);
void renderer_transform_end();

#endif
