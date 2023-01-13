
#include "renderer.h"

#define SOKOL_IMPL
#define SOKOL_GLCORE33
#define SOKOL_EXTERNAL_GL_LOADER
#include "sokol/sokol_gfx.h"
#include "sokol/sokol_gl.h"

#include "sokol/sokol_time.h"

static struct
{
    sg_pass_action pass;
    sgl_pipeline pip;
    int buffer_width;
    int buffer_height;
    bool bInitRenderer;
    uint64_t last_time;
    double deltaTime;
    double world_mousex;
    double world_mousey;
} state;

void renderer_init(void)
{
    if (state.bInitRenderer)
        return;

    stm_setup();

    sg_setup(&(sg_desc){0});
    sgl_setup(&(sgl_desc_t){0});

    state.last_time = 0;

    state.pip = sgl_make_pipeline(&(sg_pipeline_desc){
        .cull_mode = SG_CULLMODE_BACK,
        .depth = {
            .write_enabled = true,
            .compare = SG_COMPAREFUNC_LESS_EQUAL,
        },
        .colors[0] = {
            .blend = {
                .src_factor_rgb = SG_BLENDFACTOR_SRC_ALPHA,
                .dst_factor_rgb = SG_BLENDFACTOR_ONE_MINUS_SRC_ALPHA,
            },
        },
    });

    state.pass = (sg_pass_action){
        .colors[0] = {
            .action = SG_ACTION_CLEAR,
            .value = {0.0f, 0.0f, 0.0f, 1.0f},
        },
    };

    state.bInitRenderer = true;
}

void renderer_frame(void)
{
    sg_begin_default_pass(&state.pass, state.buffer_width, state.buffer_height);
    renderer_draw();
    sg_end_pass();
    sg_commit();

    state.deltaTime = stm_ms(stm_laptime(&state.last_time));
}

void renderer_resize(int width, int height)
{
    state.buffer_width = width;
    state.buffer_height = height;

    renderer_init();
}

void renderer_shutdown(void)
{
    sgl_shutdown();
    sg_shutdown();
}

double renderer_world_delta_time(void)
{
    return state.deltaTime;
}

void renderer_world_set_mouse_position(double x, double y)
{
    state.world_mousex = x;
    state.world_mousey = y;
}

double renderer_world_get_mouse_x(void)
{
    return state.world_mousex;
}

double renderer_world_get_mouse_y(void)
{
    return state.world_mousey;
}

rvect2 renderer_get_size(void)
{
    return (rvect2){state.buffer_width, state.buffer_height};
}

//
//
//

void renderer_push_matrix(void)
{
    sgl_push_matrix();
}

void renderer_pop_matrix(void)
{
    sgl_pop_matrix();
}

void renderer_begin_quads(void)
{
    sgl_begin_quads();
}

void renderer_end(void)
{
    sgl_end();
}

void renderer_v2f_c3b(float x, float y, uint8_t r, uint8_t g, uint8_t b)
{
    sgl_v2f_c3b(x, y, r, g, b);
}

//
//
//

void renderer_transform_begin(rtransform t)
{
    sgl_push_matrix();
    sgl_translate(t.position.x, t.position.y, t.position.z);
    sgl_scale(t.scale.x, t.scale.y, t.scale.z);
    sgl_rotate(t.rotation.x, 1.0f, 0.0f, 0.0f);
    sgl_rotate(t.rotation.y, 0.0f, 1.0f, 0.0f);
    sgl_rotate(t.rotation.z, 0.0f, 0.0f, 1.0f);
    sgl_translate(-(t.pivot.x * t.box.x), -(t.pivot.y * t.box.y), 0.0f);
}

void renderer_transform_end()
{
    sgl_pop_matrix();
}

//
//
//

void renderer_scissor_rect(int x, int y, int w, int h)
{
    sgl_scissor_rect(x, y, w, h, false);
}

void renderer_ortho(float left, float right, float bottom, float top)
{
    sgl_ortho(left, right, bottom, top, -0.01, 1000.0);
}

void renderer_viewport(float x, float y, float width, float height)
{
    sgl_viewport(x, y, width, height, true);
}

void renderer_defaults(void)
{
    sgl_defaults();
}

void renderer_pipeline_begin(void)
{
    sgl_push_pipeline();
    sgl_load_pipeline(state.pip);
}

void renderer_pipeline_end(void)
{
    sgl_pop_pipeline();
}

void renderer_draw(void)
{
    sgl_draw();
}

void renderer_projection(void)
{
    sgl_matrix_mode_projection();
}