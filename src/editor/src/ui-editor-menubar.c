#include "ui-editor-menubar.h"

void ui_editor_menubar_draw(void)
{
    if (igBeginMenuBar())
    {
        if (igBeginMenu("File", true))
        {
            if (igMenuItem_Bool("New", "Ctrl+N", false, true))
            {
            }
            if (igMenuItem_Bool("Open", "Ctrl+O", false, true))
            {
            }
            if (igMenuItem_Bool("Save As...", "Ctrl+S", false, true))
            {
            }
            if (igMenuItem_Bool("Exit", "", false, true))
            {
            }
            igEndMenu();
        }
        igEndMenuBar();
    }
}
