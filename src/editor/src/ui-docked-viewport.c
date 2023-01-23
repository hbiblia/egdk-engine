#include "ui-docked-viewport.h"
#include "pixel.h"
#include "pixel-gui.h"
#include "pixel-gfx.h"

static void viewport_draw_content(void);
static void viewport_viewport_render(const ImDrawList *dl, const ImDrawCmd *cmd);

void editor_gui_viewport_init(void)
{
}

void editor_gui_viewport_draw(void)
{
    igPushStyleVar_Vec2(ImGuiStyleVar_WindowPadding, (ImVec2){0.0f, 0.0f});
    if (igBegin("Viewport", false, ImGuiWindowFlags_NoMove))
    {
        viewport_draw_content();
    }
    igEnd();
    igPopStyleVar(1);
}

void viewport_draw_content(void)
{
    if (igBeginChild_Str("viewport_viewport", (ImVec2){0, 0}, true, 0))
    {
        ImDrawList *dl = igGetWindowDrawList();
        ImDrawList_AddCallback(dl, viewport_viewport_render, 0);
    }
    igEndChild();
}

void viewport_viewport_render(const ImDrawList *dl, const ImDrawCmd *cmd)
{
    (void)dl;
    const int cx = (int)cmd->ClipRect.x;
    const int cy = (int)cmd->ClipRect.y;
    const int cw = (int)(cmd->ClipRect.z - cmd->ClipRect.x);
    const int ch = (int)(cmd->ClipRect.w - cmd->ClipRect.y);

    float time = pixel_window_frame_count() / 60.0f;

    float ratio = cw / (float)ch;
    pGfx_BeginFrame(cw, ch);
    {
        pGfx_Viewport(cx, cy, cw, ch);
        pGfx_Project(0, 700 * ratio, 0, 700);
        pGfx_ClearColor(BLACK);

        pGfx_DrawCheckboard(32, 32, cw + 200, ch + 200);

        transform_begin_make((transform_t){
            .position = {100.0f, 100.0f},
            .scale = {1.0f, 1.0f},
            .rotation = time,
            .pivot = {100/2, 100/2},
        });
        pGfx_SetColor(RED);
        pGfx_DrawFilledRect(0, 0, 100, 100);
        transform_end();
    }
    pGfx_EndFrame();
}
