#ifndef _PIXEL_GUI_H
#define _PIXEL_GUI_H
#include "pixel.h"

typedef enum
{
    WINDOW_NONE = 0,
    WINDOW_NO_TITLE = 1 << 0,
    WINDOW_NO_RESIZE = 1 << 1,
    WINDOW_NO_MOVE = 1 << 2,
    WINDOW_NO_SCROLLBAR = 1 << 3,
    WINDOW_NO_COLLAPSE = 1 << 5,
    WINDOW_MENUBAR = 1 << 10,
    WINDOW_NO_DOCKING = 1 << 21,
    WINDOW_TOOLTIP = 1 << 25,
    WINDOW_POPUP = 1 << 26,
    WINDOW_MODAL = 1 << 27,
} enum_pixel_gui_window_flags;

typedef enum
{
    GUI_DIR_NONE = -1,
    GUI_DIR_LEFT = 0,
    GUI_DIR_RIGHT = 1,
    GUI_DIR_UP = 2,
    GUI_DIR_DOWN = 3,
    GUI_DIR_COUNT
} enum_pixel_gui_dir;

typedef enum
{
    MOUSE_BUTTON_NONE = 0,
    MOUSE_BUTTON_LEFT = 1 << 0,
    MOUSE_BUTTON_RIGHT = 1 << 1,
    MOUSE_BUTTON_MIDDLE = 1 << 2,
    MOUSE_BUTTON_MASK_ = MOUSE_BUTTON_LEFT | MOUSE_BUTTON_RIGHT | MOUSE_BUTTON_MIDDLE,
    MOUSE_BUTTON_DEFAULT_ = MOUSE_BUTTON_LEFT,
} enum_pixel_gui_button_flags;

typedef enum
{
    SLIDER_NONE = 0,
    SLIDER_ALWAYSCLAMP = 1 << 4,
    SLIDER_LOGARITHMIC = 1 << 5,
    SLIDER_NOROUNDTOFORMAT = 1 << 6,
    SLIDER_NOINPUT = 1 << 7,
    SLIDER_INVALIDMASK_ = 0x7000000F,
} enum_pixel_gui_slider_flags;

void pixel_gui__init(void);
void pixel_gui__begin_frame(void);
void pixel_gui__end_frame(void);
void pixel_gui__handle_event(const struct pixel_event_t *);

void pixel_gui_window_next_pos(float x, float y);
void pixel_gui_window_next_size(float width, float height);
void pixel_gui_window_next_flags(enum_pixel_gui_window_flags flags);
void pixel_gui_window_next_open(bool b_open);
bool pixel_gui_window_begin(const char *title);

bool pixel_gui_button_sm(const char *label);
bool pixel_gui_button(const char *label, float width, float height);
bool pixel_gui_button_arrow(const char *label, enum_pixel_gui_dir dir);
bool pixel_gui_button_hide(const char *id, float width, float height, enum_pixel_gui_button_flags flags);

void pixel_gui_text_next_wrap(bool wrap);
void pixel_gui_text_next_color(float r, float g, float b);
void pixel_gui_text(const char *fmt, ...);

bool pixel_gui_float_slider(const char *label, float *v, float v_min, float v_max, const char *format, enum_pixel_gui_slider_flags flags);
bool pixel_gui_float2_slider(const char *label, float v[2], float v_min, float v_max, const char *format, enum_pixel_gui_slider_flags flags);
bool pixel_gui_float3_slider(const char *label, float v[3], float v_min, float v_max, const char *format, enum_pixel_gui_slider_flags flags);
bool pixel_gui_float4_slider(const char *label, float v[4], float v_min, float v_max, const char *format, enum_pixel_gui_slider_flags flags);

bool pixel_gui_int_slider(const char *label, int *v, int v_min, int v_max, const char *format, enum_pixel_gui_slider_flags flags);
bool pixel_gui_int2_slider(const char *label, int v[2], int v_min, int v_max, const char *format, enum_pixel_gui_slider_flags flags);
bool pixel_gui_int3_slider(const char *label, int v[3], int v_min, int v_max, const char *format, enum_pixel_gui_slider_flags flags);
bool pixel_gui_int4_slider(const char *label, int v[4], int v_min, int v_max, const char *format, enum_pixel_gui_slider_flags flags);

bool pixel_gui_color3(const char* label, float col[3]);
bool pixel_gui_color4(const char* label, float col[4]);
bool pixel_gui_color_button(const char* desc_id, float col[4], float width, float height);

void pixel_gui_begin_view_list();
void pixel_gui_end_view_list();
void pixel_gui_push_view_list();

void pixel_gui_separator(void);
void pixel_gui_end(void);

#endif
