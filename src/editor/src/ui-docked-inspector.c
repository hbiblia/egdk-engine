#include "ui-docked-inspector.h"
#include "pixel-gui.h"

void editor_gui_inspector_init(void)
{
}

void editor_gui_inspector_draw(void)
{
    if (igBegin("Inspector", false, ImGuiWindowFlags_NoMove))
    {
    }
    igEnd();
}
