/**
 * Panel Tool
 *
 *
 */

#include "panel-tool.h"
#include "pixel.h"
#include "editor-gui-browser.h"

void panel_tool_draw(void)
{
    int height = pixel_window_height();

    pixel_gui_window_next_size(300, height);
    pixel_gui_window_next_pos(0, 0);
    pixel_gui_window_next_flags(WINDOW_NO_MOVE | WINDOW_NO_TITLE | WINDOW_NO_RESIZE | WINDOW_NO_SCROLLBAR);
    if (pixel_gui_window_begin("Tools"))
    {
        editor_gui_browser_draw();

        pixel_gui_end();
    }
}