/**
 * pixel-gui
 *
 * Mientras utilizamos cimgui pasaremos su API
 * para pixel-gui.
 *
 */

#include "pixel-gui.h"

#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include "cimgui/cimgui.h"

#include "sokol/sokol_app.h"
#include "sokol/sokol_gfx.h"
#include "sokol/sokol_glue.h"
#define SOKOL_IMGUI_IMPL
#include "sokol/sokol_imgui.h"

struct pixel_gui_window_desc
{
    bool b_open;
    enum_pixel_gui_window_flags flags;
} gui_window_state;

struct pixel_gui_text_desc
{
    ImVec4 color;
    bool wrap;
} gui_text_state;
static struct pixel_gui_text_desc gui_text_state_save;

void pixel_gui__init(void)
{
    simgui_setup(&(simgui_desc_t){0});
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

/**
 * pixel-gui-window
 * window
 *
 */

void pixel_gui_window_next_pos(float x, float y)
{
    igSetNextWindowPos((ImVec2){x, y}, ImGuiCond_Always, (ImVec2){0, 0});
}

void pixel_gui_window_next_size(float width, float height)
{
    igSetNextWindowSize((ImVec2){width, height}, ImGuiCond_Always);
}

void pixel_gui_window_next_flags(enum_pixel_gui_window_flags flags)
{
    gui_window_state.flags = flags;
}

void pixel_gui_window_next_open(bool b_open)
{
    gui_window_state.b_open = b_open;
}

bool pixel_gui_window_begin(const char *title)
{
    bool b_value = igBegin(title, &gui_window_state.b_open, gui_window_state.flags);
    return b_value;
}

/**
 * pixel-gui-button
 * button
 *
 */

bool pixel_gui_button(const char *label, float width, float height)
{
    bool b_value = false;
    b_value = igButton(label, (ImVec2){width, height});
    return b_value;
}

bool pixel_gui_button_sm(const char *label)
{
    bool b_value = false;
    b_value = igSmallButton(label);
    return b_value;
}

bool pixel_gui_button_hide(const char *id, float width, float height, enum_pixel_gui_button_flags flags)
{
    bool b_value = false;
    b_value = igInvisibleButton(id, (ImVec2){width, height}, flags);
    return b_value;
}

bool pixel_gui_button_arrow(const char *label, enum_pixel_gui_dir dir)
{
    bool b_value = false;
    b_value = igArrowButton(label, dir);
    return b_value;
}

/**
 * pixel-gui-text
 * text
 *
 */

void pixel_gui_text_next_wrap(bool wrap)
{
    gui_text_state_save.wrap = gui_text_state.wrap;
    gui_text_state.wrap = wrap;
}

void pixel_gui_text_next_color(float r, float g, float b)
{
    gui_text_state_save.color = gui_text_state.color;
    gui_text_state.color = (ImVec4){r, g, b, 1.0f};
}

void pixel_gui_text(const char *fmt, ...)
{
    if (gui_text_state.wrap)
    {
        igTextWrapped(fmt);
    }
    else if (gui_text_state.color.x != 0 || gui_text_state.color.y != 0 || gui_text_state.color.z != 0)
    {
        igTextColored(gui_text_state.color, fmt);
    }
    else
    {
        igText(fmt);
    }

    gui_text_state.wrap = gui_text_state_save.wrap;
    gui_text_state.color = gui_text_state_save.color;
}

/**
 * pixel-gui-float
 * float
 *
 */

bool pixel_gui_float_slider(const char *label, float *v, float v_min, float v_max, const char *format, enum_pixel_gui_slider_flags flags)
{
    bool b_value = false;
    b_value = igSliderFloat(label, v, v_min, v_max, format, flags);
    return b_value;
}

bool pixel_gui_float2_slider(const char *label, float v[2], float v_min, float v_max, const char *format, enum_pixel_gui_slider_flags flags)
{
    bool b_value = false;
    b_value = igSliderFloat2(label, v, v_min, v_max, format, flags);
    return b_value;
}

bool pixel_gui_float3_slider(const char *label, float v[3], float v_min, float v_max, const char *format, enum_pixel_gui_slider_flags flags)
{
    bool b_value = false;
    b_value = igSliderFloat3(label, v, v_min, v_max, format, flags);
    return b_value;
}

bool pixel_gui_float4_slider(const char *label, float v[4], float v_min, float v_max, const char *format, enum_pixel_gui_slider_flags flags)
{
    bool b_value = false;
    b_value = igSliderFloat4(label, v, v_min, v_max, format, flags);
    return b_value;
}

/**
 * pixel-gui-int
 * int
 *
 */

bool pixel_gui_int_slider(const char *label, int *v, int v_min, int v_max, const char *format, enum_pixel_gui_slider_flags flags)
{
    bool b_value = false;
    b_value = igSliderInt(label, v, v_min, v_max, format, flags);
    return b_value;
}

bool pixel_gui_int2_slider(const char *label, int v[2], int v_min, int v_max, const char *format, enum_pixel_gui_slider_flags flags)
{
    bool b_value = false;
    b_value = igSliderInt2(label, v, v_min, v_max, format, flags);
    return b_value;
}

bool pixel_gui_int3_slider(const char *label, int v[3], int v_min, int v_max, const char *format, enum_pixel_gui_slider_flags flags)
{
    bool b_value = false;
    b_value = igSliderInt3(label, v, v_min, v_max, format, flags);
    return b_value;
}

bool pixel_gui_int4_slider(const char *label, int v[4], int v_min, int v_max, const char *format, enum_pixel_gui_slider_flags flags)
{
    bool b_value = false;
    b_value = igSliderInt4(label, v, v_min, v_max, format, flags);
    return b_value;
}

/**
 * pixel-gui-color
 * color
 *
 */

// CIMGUI_API bool igColorPicker4(const char* label,float col[4],ImGuiColorEditFlags flags,const float* ref_col);
// CIMGUI_API bool igColorButton(const char* desc_id,const ImVec4 col,ImGuiColorEditFlags flags,const ImVec2 size);

bool pixel_gui_color3(const char* label, float col[3])
{
    bool b_value = false;
    b_value = igColorEdit3(label, col, ImGuiColorEditFlags_DefaultOptions_);
    return b_value;
}

bool pixel_gui_color4(const char* label, float col[4])
{
    bool b_value = false;
    b_value = igColorEdit4(label, col, ImGuiColorEditFlags_DefaultOptions_);
    return b_value;
}

bool pixel_gui_color_button(const char* desc_id, float col[4], float width, float height)
{
    ImVec4 new_color = (ImVec4){col[0], col[1], col[2], col[3]};
    bool b_value = false;
    b_value = igColorButton(desc_id, new_color, ImGuiColorEditFlags_DefaultOptions_, (ImVec2){width, height});
    col[0] = new_color.x;
    col[1] = new_color.y;
    col[2] = new_color.z;
    col[3] = new_color.w;
    return b_value;
}

/**
 * pixel-gui-view-list
 * view_list
 *
 */

void pixel_gui_begin_view_list()
{
    igColumns(2, "view_list_test", true);
}

void pixel_gui_end_view_list()
{
    igColumns(1, "view_list_test", false);
}

void pixel_gui_push_view_list()
{
    igNextColumn();
}

/**
 * pixel-gui-
 * general
 *
 */

void pixel_gui_separator(void)
{
    igSeparator();
}

void pixel_gui_end(void)
{
    igEnd();
}