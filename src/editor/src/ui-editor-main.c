/**
 * DOCKED MAIN
 *
 */

#include "ui-editor-main.h"
#include "pixel/pixel.h"
#include "ui-docked-viewport.h"
#include "ui-docked-browser.h"
#include "ui-docked-hierarchy.h"
#include "ui-docked-inspector.h"
#include "ui-editor-menubar.h"

static void docked_begin_content(void);

void ui_editor_main_init(void)
{
    pResource_ProjectInit("D:/Github/egdk-engine/examples/sprites");

    editor_gui_browser_init();
    editor_gui_viewport_init();
    editor_gui_hierarchy_init();
    editor_gui_inspector_init();
}

void ui_editor_main_draw(void)
{
    docked_begin_content();
    {
        // ----------------------
        // Menubar
        // ----------------------
        ui_editor_menubar_draw();

        // ----------------------
        // Pintamos los docked registrados
        // ----------------------
        editor_gui_browser_draw();
        editor_gui_viewport_draw();
        editor_gui_hierarchy_draw();
        editor_gui_inspector_draw();
    }
    igEnd();
}

void docked_begin_content(void)
{
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    const ImGuiViewport *viewport = igGetMainViewport();

    igSetNextWindowPos(viewport->Pos, 0, (ImVec2){});
    igSetNextWindowSize(viewport->Size, 0);
    igSetNextWindowViewport(viewport->ID);

    igPushStyleVar_Float(ImGuiStyleVar_WindowRounding, 0.0f);
    igPushStyleVar_Float(ImGuiStyleVar_WindowBorderSize, 0.0f);
    igPushStyleVar_Vec2(ImGuiStyleVar_WindowPadding, (ImVec2){});

    window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
                    ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
        window_flags |= ImGuiWindowFlags_NoBackground;

    igBegin("DockSpace", NULL, window_flags);
    igPopStyleVar(1);
    igPopStyleVar(2);

    ImGuiIO *io = igGetIO();
    if (io->ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspace_id = igGetID_Str("MyDockSpace");
        igDockSpace(dockspace_id, (ImVec2){}, dockspace_flags, NULL);

        static bool first_time = true;
        if (first_time)
        {
            first_time = false;

            igDockBuilderRemoveNode(dockspace_id); // clear any previous layout
            igDockBuilderAddNode(dockspace_id, dockspace_flags | ImGuiDockNodeFlags_DockSpace);
            igDockBuilderSetNodeSize(dockspace_id, viewport->Size);

            ImGuiID dock_id_left = igDockBuilderSplitNode(dockspace_id, ImGuiDir_Left, 0.2f, NULL, &dockspace_id);
            ImGuiID dock_id_right = igDockBuilderSplitNode(dockspace_id, ImGuiDir_Right, 0.3f, NULL, &dockspace_id);
            ImGuiID dock_id_left_up = igDockBuilderSplitNode(dock_id_left, ImGuiDir_Up, 0.5f, NULL, &dock_id_left);

            igDockBuilderDockWindow("Scene Hierarchy", dock_id_left_up);
            igDockBuilderDockWindow("Inspector", dock_id_right);
            igDockBuilderDockWindow("Browser", dock_id_left);
            igDockBuilderDockWindow("Viewport", dockspace_id);
        }
    }
}