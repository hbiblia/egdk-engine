#include "rcamera.h"
#include "renderer.h"

static rcamera cameras[RCAMERA_LAST];
static int camera_active = RCAMERA_NONE;

void rcamera_ortho(float l, float r, float b, float t)
{
    renderer_ortho(l, r, b, t);
}

void rcamera_viewport(rcamera camera)
{
    renderer_viewport(camera.viewport.x, camera.viewport.y, camera.viewport.w, camera.viewport.h);
}

void rcamera_scissor(rcamera camera)
{
    renderer_scissor_rect(camera.viewport.x, camera.viewport.y, camera.viewport.w, camera.viewport.h);
}

void rcamera_init(void)
{
}

void rcamera_active_set_default(void)
{
    cameras[camera_active].viewport = (rrect){0, 0, 0, 0};
    cameras[camera_active].transform = (rtransform){
        .position = {0, 0, 0},
        .scale = {1, 1, 1},
        .rotation = {0, 0, 0},
        .pivot = {0, 0},
    };
}

void rcamera_active_set_size(int width, int height)
{
    cameras[camera_active].viewport.w = width;
    cameras[camera_active].viewport.h = height;
}

void rcamera_begin(void)
{
    rcamera camera = cameras[camera_active];
    float aspect = (float)camera.viewport.w / (float)camera.viewport.h;
    float scale = 700.0f;

    rcamera_scissor(camera);
    rcamera_viewport(camera);

    renderer_defaults();
    renderer_pipeline_begin();
    renderer_projection();

    float ortho_size = (aspect * scale);
    rcamera_ortho(-ortho_size, +ortho_size, -scale, +scale);
    renderer_push_matrix();
}

void rcamera_end(void)
{
    // renderer_draw();
    renderer_pop_matrix();
    renderer_pipeline_end();
}