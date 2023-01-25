/**
 * EGDKEditor
 *
 *
 *
 *
 *
 */

#include <stdio.h>
#include "pixel/pixel.h"
#include "ui-editor-main.h"
#include "single-file.h"

#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

static void init_fn()
{
    printf("Init Pixel\n");

    eSingleFile_Init();
    ui_editor_main_init();

    lua_State *l = luaL_newstate();
    luaL_openlibs(l);
    luaL_dostring(l, "print('Hola Mundo del Lua')");
    lua_close(l);
}

static void draw_fn(float deltaTime)
{
    ui_editor_main_draw();
}

static void shutdown_fn()
{
    eSingleFile_Shutdown();
}

int main(int argc, char *argv[])
{
    pWindow_Main(&(pixel_window_desc){
        .title = "EGDKEditor - v0.0.1",
        .width = 1280,
        .height = 720,
        .init_fn = init_fn,
        .draw_fn = draw_fn,
        .shutdown_fn = shutdown_fn,
    });
}