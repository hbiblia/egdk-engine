/**
 * pixel-gui
 *
 * Mientras utilizamos cimgui pasaremos su API
 * para pixel-gui.
 *
 */

#include "pixel-gui.h"

#include "sokol/sokol_app.h"
#include "sokol/sokol_gfx.h"
#include "sokol/sokol_glue.h"
#define SOKOL_IMGUI_IMPL
#include "sokol/sokol_imgui.h"

void pixel_gui__init(void)
{
    simgui_setup(&(simgui_desc_t){0});
    
    ImGuiIO *io = igGetIO();
    io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;   // Enable Docking
    io->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable Multi-Viewport
}

void pixel_gui__begin_frame(void)
{
    simgui_new_frame(&(simgui_frame_desc_t){
        .width = pixel_window_width(),
        .height = pixel_window_height(),
        .delta_time = pixel_window_delta_time(),
        .dpi_scale = pixel_window_dpi_scale(),
    });
}

void pixel_gui__end_frame(void)
{
    simgui_render();
}

void pixel_gui__handle_event(const pixel_event_t *evt)
{
    const sapp_event *e = (sapp_event *)evt->event;
    simgui_handle_event(e);
}