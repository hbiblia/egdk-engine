/**
 * EGDKEditor
 *
 *
 *
 *
 *
 */

#include <stdio.h>
#include "pixel.h"
#include "panel-tool.h"

static void init_fn()
{
    printf("Init Pixel\n");
}

static void draw_fn(float deltaTime)
{
    panel_tool_draw();
}

int main(int argc, char *argv[])
{
    pixel_window_main(&(pixel_window_desc){
        .title = "EGDKEditor - v0.0.1",
        .init_fn = init_fn,
        .draw_fn = draw_fn,
    });
}