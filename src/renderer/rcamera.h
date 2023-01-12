#ifndef RCAMERA_H
#define RCAMERA_H
#include <stdio.h>
#include "rmath.h"

typedef enum {
    RCAMERA_NONE,
    RCAMERA_EDITOR,
    RCAMERA_GAME0,
    RCAMERA_GAME1,
    RCAMERA_GAME2,
    RCAMERA_GAME3,
    RCAMERA_CINEMATIC,
    RCAMERA_LAST
}rcamera_type;

typedef struct {
    rtransform transform;
    rrect viewport;
}rcamera;

void rcamera_end();
void rcamera_begin();
void rcamera_viewport(rcamera camera);
void rcamera_scissor(rcamera camera);
void rcamera_ortho(float l, float r, float b, float t, float n, float f);
void rcamera_active_set_default(void);
void rcamera_active_set_size(int width, int height);

#endif