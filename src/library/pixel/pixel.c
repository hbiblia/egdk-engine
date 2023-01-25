#include "pixel.h"

#include "pixel-ecs.h"

#include "path_fn.h"
#include "string_fn.h"
#include "file_fn.h"

#define SOKOL_IMPL
#define SOKOL_NO_ENTRY
#include "sokol/sokol_gfx.h"
#include "sokol/sokol_app.h"
#include "sokol/sokol_glue.h"
#include "sokol/sokol_gp.h"

#define SOKOL_IMGUI_IMPL
#include "sokol/sokol_imgui.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

/***
 *
 *  struct PixelBase
 *
 *  Anteriormente tenia varios archivos para cada procesos
 *  pero con el tiempo mientras escribia vi que no eran tan
 *  importante aparte de una mejor organizacion del proyecto.
 *
 *  Pero me encontre que tener todo en un solo archivo era
 *  mucho mas comodo que tener que ir a cada archivo diferente
 *  para agregar, actualizar o mejorar algo.
 *
 *  Al momento de escribir esto, estoy utilizando sokol_gp
 *  para la geometria y otras cosas basicas que en algun momento
 *  quiero hacer la mia propia.
 */

struct PixelBase
{
    struct
    {
        void (*init_fn)(void);                   //
        void (*draw_fn)(float dt);               //
        void (*event_fn)(const pixel_event_t *); //
        void (*shutdown_fn)(void);               //

        struct
        {
            char *pathr[RESOURCE_LAST];
            texture_t icons[RESOUCE_ICONS];
            bool bpathCurrentChange;
        } Resource;
    } Window;
} pixel;

/***
 *
 *  struct PixelBase
 *
 *  PixelApp
 *
 */

static void pApp_Init(void)
{
    sg_context_desc ctx = sapp_sgcontext();
    sg_setup(&(sg_desc){.context = ctx});
    simgui_setup(&(simgui_desc_t){0});
    pGfx_Init();
    pResource_Init();
    pEcs_Init();

    ImGuiIO *io = igGetIO();
    io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;   // Enable Docking
    io->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable Multi-Viewport

    if (pixel.Window.init_fn)
        pixel.Window.init_fn();
}

static void pApp_Event(const sapp_event *evt)
{
    simgui_handle_event(evt);

    if (pixel.Window.event_fn)
        pixel.Window.event_fn(NULL);
}

static void pApp_Frame(void)
{
    simgui_new_frame(&(simgui_frame_desc_t){
        .width = pWindow_GetWidth(),
        .height = pWindow_GetHeight(),
        .delta_time = pWindow_DeltaTime(),
        .dpi_scale = pWindow_DpiScale(),
    });

    if (pixel.Window.draw_fn)
        pixel.Window.draw_fn((float)pWindow_DeltaTime());

    pEcs_Progress();

    sg_pass_action pass_action = {0};
    sg_begin_default_pass(&pass_action, pWindow_GetWidth(), pWindow_GetHeight());

    simgui_render();
    sg_end_pass();
    sg_commit();
}

static void pApp_Shutdown()
{
    if (pixel.Window.shutdown_fn)
        pixel.Window.shutdown_fn();

    pGfx_Shutdown();
    simgui_shutdown();
    sapp_quit();
    exit(-1);
}

/***
 *
 *  struct PixelBase
 *
 *  PixelWindow
 *
 */

void pWindow_Main(const pixel_window_desc *desc)
{
    pixel.Window.init_fn = desc->init_fn;
    pixel.Window.draw_fn = desc->draw_fn;
    pixel.Window.event_fn = desc->event_fn;
    pixel.Window.shutdown_fn = desc->shutdown_fn;

    sapp_run(&(sapp_desc){
        .window_title = desc->title,
        .width = desc->width,
        .height = desc->height,
        .init_cb = pApp_Init,
        .frame_cb = pApp_Frame,
        .event_cb = pApp_Event,
        .cleanup_cb = pApp_Shutdown,
    });
}

int pWindow_GetWidth(void)
{
    return sapp_width();
}

int pWindow_GetHeight(void)
{
    return sapp_height();
}

double pWindow_DeltaTime(void)
{
    return sapp_frame_duration();
}

uint64_t pWindow_FrameCount(void)
{
    return sapp_frame_count();
}

float pWindow_DpiScale(void)
{
    return sapp_dpi_scale();
}

/***
 *
 *  struct PixelBase
 *
 *  PixelGfx
 *
 */

void pGfx_Init(void)
{
    sgp_setup(&(sgp_desc){0});
}

void pGfx_Shutdown(void)
{
    sgp_shutdown();
}

void pGfx_BeginFrame(int width, int height)
{
    sgp_begin(width, height);
}

void pGfx_EndFrame(void)
{
    sgp_flush();
    sgp_end();
}

void pGfx_Viewport(int x, int y, int width, int height)
{
    sgp_viewport(x, y, width, height);
}

void pGfx_Project(float left, float right, float top, float bottom)
{
    sgp_project(left, right, top, bottom);
}

void pGfx_ClearColor(color_t color)
{
    pGfx_SetColor(color);
    sgp_clear();
}

void pGfx_SetColor(color_t color)
{
    float r = (float)color.r / 255;
    float g = (float)color.g / 255;
    float b = (float)color.b / 255;
    float a = (float)color.a / 255;
    sgp_set_color(r, g, b, a);
}

void pGfx_SetRotate(float theta, float x, float y)
{
    sgp_rotate_at(theta, x, y);
}

void pGfx_SetScale(float sx, float sy, float x, float y)
{
    sgp_scale_at(sx, sy, x, y);
}

void pGfx_SetTranslate(float x, float y)
{
    sgp_translate(x, y);
}

void pGfx_DrawFilledRect(float x, float y, float w, float h)
{
    sgp_draw_filled_rect(x, y, w, h);
}

void pGfx_DrawCheckboard(int width, int height, int screen_width, int screen_height)
{
    pGfx_SetColor((color_t){25, 25, 25, 255});
    sgp_clear();
    pGfx_SetColor((color_t){35, 35, 35, 255});

    for (int y = 0; y < screen_height / height + 1; y++)
        for (int x = 0; x < screen_width / width + 1; x++)
            if ((x + y) % 2 == 0)
                pGfx_DrawFilledRect(x * width, y * height, width, height);
    sgp_reset_color();
}

/***
 *
 *  struct PixelBase
 *
 *  PixelTransform
 *
 */

void pTransform_BeginMake(transform_t t)
{
    sgp_push_transform();
    pGfx_SetTranslate(t.position.x, t.position.y);
    pGfx_SetScale(t.scale.x, t.scale.y, t.pivot.x, t.pivot.y);
    pGfx_SetRotate(t.rotation, t.pivot.x, t.pivot.y);
}

void pTransform_End()
{
    sgp_pop_transform();
}

/***
 *
 *  struct PixelBase
 *
 *  PixelTexture
 *
 */

texture_t pTexture_LoadFile(const char *filename)
{
    texture_t texture = {0};

    int comp;
    stbi_uc *data = stbi_load(filename, &texture.width, &texture.height, &comp, STBI_rgb_alpha);

    if (data != NULL)
    {
        sg_image d = sg_make_image(&(sg_image_desc){
            .width = texture.width,
            .height = texture.height,
            .data.subimage[0][0] = {
                .ptr = data,
                .size = (size_t){texture.width * texture.height * 4},
            },
        });
        texture.id = d.id;

        stbi_image_free(data);
    }

    return texture;
}

void pTexture_Free(texture_t texture)
{
    sg_image d = (sg_image){.id = texture.id};
    sg_destroy_image(d);
}

/***
 *
 *  struct PixelBase
 *
 *  PixelResource
 *
 */

void pResource_Init(void)
{
    printf("INFO: Resource Init\n");
    pixel.Window.Resource.pathr[RESOURCE_PATH_ASSETS_ENGINE] = PathBuild(PathPwd(), "resource", NULL);
    printf("A: %s\n", pixel.Window.Resource.pathr[RESOURCE_PATH_ASSETS_ENGINE]);

    pixel.Window.Resource.icons[RESOUCE_ICON_FOLDER] = pTexture_LoadFile(PathBuild(pixel.Window.Resource.pathr[RESOURCE_PATH_ASSETS_ENGINE], "textures", "folder.png", NULL));
}

void pResource_ProjectInit(const char *path)
{
    pixel.Window.Resource.pathr[RESOURCE_PATH_PROJECT] = PathNormalize(path);
    pixel.Window.Resource.pathr[RESOURCE_PATH_CONFIG] = PathBuild(path, "config", NULL);
    pixel.Window.Resource.pathr[RESOURCE_PATH_ASSETS_DEFAULT] = PathBuild(path, "Content", NULL);
    pResource_ChangeCurrentContentFolder(pixel.Window.Resource.pathr[RESOURCE_PATH_ASSETS_DEFAULT], NULL);
}

void pResource_ChangeCurrentContentFolder(const char *path, const char *filename)
{
    pixel.Window.Resource.bpathCurrentChange = true;
    pixel.Window.Resource.pathr[RESOURCE_PATH_ASSETS_CURRENT] = PathBuild(path, filename, NULL);
}

bool pResource_CurrentContentFolderHasChanges(void)
{
    bool r = pixel.Window.Resource.bpathCurrentChange;
    pixel.Window.Resource.bpathCurrentChange = false;
    return r;
}

const char *pResource_GetPath(pixel_resource_paths path)
{
    return pixel.Window.Resource.pathr[path];
}

unsigned int pResource_GetIconId(pixel_resource_icons icon)
{
    return pixel.Window.Resource.icons[icon].id;
}
