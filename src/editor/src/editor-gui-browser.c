/**
 * Browser GUI
 *
 *
 */

#include "editor-gui-browser.h"
#include "editor-browser.h"
#include "pixel.h"
#include "file_fn.h"
#include "string_fn.h"
#include "path_fn.h"
#include "pixel-gui.h"
#include <glib.h>

static GPtrArray *dirCurrentFolder = NULL;
static bool test_oneload_path = false;

struct browser_t
{
    char *filter;
} browser_d;

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
    if (dirCurrentFolder == NULL)
        return;

    if (pixel_gui_begin_view_list(64))
    {
        for (int i = 0; i < dirCurrentFolder->len; i++)
        {
            FileDirFile *file = g_ptr_array_index(dirCurrentFolder, i);
            if (file->image_id == 0)
                continue;

            // filtro
            if (strcmp(browser_d.filter, "") != 0 && !StringMatch(browser_d.filter, file->name))
                continue;

            pixel_gui_begin_view_list_child();
            {
                /*********
                 * ICONO *
                 *********/
                pixel_gui_style_color(STYLE_COLOR_BUTTON, 0, 0, 0, 0.2f);
                if (pixel_gui_button_image(file->name, file->image_id, 64, 64))
                {
                }
                pixel_gui_style_color_clear();

                /********
                 * TEXT *
                 ********/
                pixel_gui_text_next_wrap(true);
                pixel_gui_text(file->name);
            }
            pixel_gui_end_view_list_child();
        }
        pixel_gui_end_view_list();
    }
}

void gui_browser_filter_list_file(void)
{
    if (pixel_gui_input_text("Filter", browser_d.filter))
    {
    }
}

void editor_gui_browser_draw(void)
{
    if (test_oneload_path == FALSE)
    {
        browser_d.filter = g_new0(char *, 1);
        test_oneload_path = TRUE;
        dirCurrentFolder = browser_list_dir_content("D:/Github/egdk-engine/examples/sprites/Content");
    }

    gui_browser_toolbar();
    gui_browser_filter_list_file();
    gui_browser_list_file();
}
