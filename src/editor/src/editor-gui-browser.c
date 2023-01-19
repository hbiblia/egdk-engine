/**
 * Browser GUI
 *
 *
 */

#include "editor-gui-browser.h"
#include "pixel.h"
#include "file_fn.h"

static GPtrArray *dirCurrentFolder;
static bool test_oneload_path = false;

void gui_browser_toolbar()
{
    // Toolbar buttons
    if (pixel_gui_button("+", 25.0f, 0.0f))
    {
        printf("Add file browser\n");
    }
    pixel_gui_separator();
}

void gui_browser_list_file()
{
    pixel_gui_begin_view_list();
    {
        for (int i = 0; i < dirCurrentFolder->len; i++)
        {
            FileDirFile *file = g_ptr_array_index(dirCurrentFolder, i);
            pixel_gui_text(file->name);
            pixel_gui_push_view_list();
        }
    }
    pixel_gui_end_view_list();
}

void editor_gui_browser_draw(void)
{
    if (test_oneload_path == FALSE)
    {
        test_oneload_path = TRUE;
        dirCurrentFolder = FileReaddir("D:/Github/egdk-engine/examples/sprites/Content");
    }

    gui_browser_toolbar();
    gui_browser_list_file();
}