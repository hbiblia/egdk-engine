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
#include "ui-editor-main.h"
#include "pixel-resource.h"

#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

static void init_fn()
{
    printf("Init Pixel\n");
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

int main(int argc, char *argv[])
{
    pixel_window_main(&(pixel_window_desc){
        .title = "EGDKEditor - v0.0.1",
        .init_fn = init_fn,
        .draw_fn = draw_fn,
    });
}