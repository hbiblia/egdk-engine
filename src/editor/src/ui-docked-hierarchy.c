#include "ui-docked-hierarchy.h"
#include "pixel-gui.h"
#include "flecs/flecs.h"

static void hierarchy_menu_context_open(const char *name, ecs_entity_t e);

void editor_gui_hierarchy_init(void)
{
}

void editor_gui_hierarchy_draw(void)
{
    if (igBegin("Scene Hierarchy", false, ImGuiWindowFlags_NoMove))
    {
        igSameLine(0,0);
        if(igSmallButton("New entity")){}
        igSeparator();
    }
    igEnd();
}

void hierarchy_menu_context_open(const char *name, ecs_entity_t e)
{
    if (igIsItemClicked(ImGuiMouseButton_Right))
    {
        igOpenPopup_Str("hierarchy-menu-context", 0);
    }

    if (igBeginPopupContextItem("hierarchy-menu-context", ImGuiPopupFlags_MouseButtonRight))
    {
        igText("Entity ( %s )", name);
        igSeparator();

        if (igSelectable_Bool("Delete", false, 0, (ImVec2){0, 0}))
        {
        }
        if (igSelectable_Bool("Rename", false, 0, (ImVec2){0, 0}))
        {
        }
        igSeparator();
        if (igSelectable_Bool("Duplicate", false, 0, (ImVec2){0, 0}))
        {
        }
        igEndPopup();
    }
}