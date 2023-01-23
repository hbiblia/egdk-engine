/**
 * pixel-window
 *
 * Nos permite crear un ventana segun el sistema donde nos encontremos
 * Windows,Linux y Mac son manejadas ahora mismo por sokol_app aun que
 * si se quiere mejores func es mejor implementar SDL2 para la window.
 *
 * TODO: Android, IOS y Otros
 *
 */

#include "pixel-window.h"
#include "pixel-resource.h"
#include "pixel-gfx.h"

// SOKOL IMPL
#define SOKOL_IMPL
#define SOKOL_NO_ENTRY
#include "sokol/sokol_gfx.h"
#include "sokol/sokol_app.h"
#include "sokol/sokol_glue.h"
#include "sokol/sokol_gp.h"

static pixel_window_desc *desc_main;

/**
 * defaul_ son func privadas que utiliza sokol_app
 * para el render-draw, event y inicializar
 *
 */
static void default_init_app(void)
{
    sg_context_desc ctx = sapp_sgcontext();
    sg_setup(&(sg_desc){.context = ctx});

    pixel_gui__init();
    pGfx_Init();
    pixel_resource_init();

    if (desc_main->init_fn)
    {
        desc_main->init_fn();
    }
}

static void default_frame_app(void)
{
    pixel_gui__begin_frame();
    {
        if (desc_main->draw_fn)
        {
            desc_main->draw_fn((float)sapp_frame_duration());
        }
    }
    sg_pass_action pass_action = {0};
    sg_begin_default_pass(&pass_action, sapp_width(), sapp_height());
    pixel_gui__end_frame();
    sg_end_pass();
    sg_commit();
}

static void default_event_app(const sapp_event *event)
{
    pixel_gui__handle_event(&(pixel_event_t){.event = event});

    // event update
    if (desc_main->event_fn)
    {
        desc_main->event_fn(NULL);
    }
}

static void default_shutdown(void)
{
    if (desc_main->shutdown_fn)
    {
        desc_main->shutdown_fn();
    }

    pGfx_Shutdown();
    sapp_quit();
    exit(-1);
}

/**
 * Mantenemos la ventana abierta, vamos a tener unas configuraciones
 * para las propiedades de la ventana como:
 *  1 - Titulo,
 *  2 - Size width
 *  3 - Size height
 *  4 - Function Init,
 *  5 - Function Update,
 *  6 - Function Event,
 *  7 - Function Shutdown
 *
 */

void pixel_window_main(const pixel_window_desc *desc)
{
    desc_main = desc;

    sapp_run(&(sapp_desc){
        .window_title = desc->title,
        .width = 1280,
        .height = 720,
        .init_cb = default_init_app,
        .frame_cb = default_frame_app,
        .event_cb = default_event_app,
        .cleanup_cb = default_shutdown,
    });
}

int pixel_window_width(void)
{
    return sapp_width();
}

int pixel_window_height(void)
{
    return sapp_height();
}

double pixel_window_delta_time(void)
{
    return sapp_frame_duration();
}

uint64_t pixel_window_frame_count(void)
{
    return sapp_frame_count();
}

float pixel_window_dpi_scale(void)
{
    return sapp_dpi_scale();
}