/**
 * Browser GUI
 *
 *
 */

#include "ui-docked-browser.h"
#include "editor-browser.h"
#include <glib.h>

#include "pixel.h"
#include "pixel-gui.h"
#include "file_fn.h"
#include "string_fn.h"
#include "path_fn.h"
#include "pixel-resource.h"

static GPtrArray *dirCurrentFolder = NULL;
static bool test_oneload_path = false;

struct browser_t
{
    char *filter;
} browser_d;

static void browser_draw_content(void);
static void browser_menu_context_open(FileDirFile *file);
static void browser_double_click_open(FileDirFile *file);
static void browser_drag_and_drop(FileDirFile *file);

void editor_gui_browser_init(void)
{
    browser_d.filter = g_new0(char, 1);
}

void editor_gui_browser_destroy(void)
{
    g_free(browser_d.filter);
}

void editor_gui_browser_draw(void)
{
    if (igBegin("Browser", false, ImGuiWindowFlags_NoMove))
    {
        browser_draw_content();
    }
    igEnd();
}

void browser_draw_content(void)
{
    /**
     * prCurrentContentFolderHasChanges identifica cuando se cambia de
     * folder y actualiza la lista de contenido.
     */
    if (prCurrentContentFolderHasChanges())
    {
        FileReaddirFree(dirCurrentFolder);
        dirCurrentFolder = browser_list_dir_content(prGetPath(RESOURCE_PATH_ASSETS_CURRENT));
    }

    /***********
     * TOOLBAR *
     ***********/
    if (pgButton("+", 25.0f, 0.0f))
    {
        printf("Add file browser\n");
    }
    igSameLine(0.0f, 6.0f);
    if (pgButton("Home", 35.0f, 0.0f))
    {
        browser_home_path();
    }
    igSameLine(0.0f, 1.0f);
    if (pgButton("Back", 35.0f, 0.0f))
    {
        browser_move_back_path();
    }
    pgSeparator();

    /************************************
     * FILTRO PARA LA LISTA DE ARCHIVOS *
     ************************************/
    if (pgInputText("Filter", browser_d.filter))
    {
    }

    /***************************************
     * LISTA DE ARCHIVOS DEL FOLDER ACTIVO *
     ***************************************/
    const ImVec2 panel_size;
    igGetContentRegionAvail(&panel_size);
    const int icon_size = 64;
    int column_count = (int)(panel_size.x / icon_size);
    column_count = column_count < 1 ? 1 : column_count;

    if (pgBeginViewList("browser_list_file_content", column_count))
    {
        const int len = dirCurrentFolder == NULL ? 0 : dirCurrentFolder->len;
        for (int i = 0; i < len; i++)
        {
            FileDirFile *file = g_ptr_array_index(dirCurrentFolder, i);
            if (file->image_id == 0)
                continue;

            const char *name_file = file->name;

            // filtro
            if (strcmp(browser_d.filter, "") != 0 && !StringMatch(browser_d.filter, name_file))
                continue;

            pgBeginChildViewList(name_file);
            {
                /*********
                 * ICONO *
                 *********/
                pgStyleColor(ImGuiCol_Button, 0, 0, 0, 0.2f);
                pgButtonImage(name_file, file->image_id, 64.0f, 64.0f);
                pgStyleColorClear(1);

                /***************
                 * DRAG SOURCE *
                 ***************/
                browser_drag_and_drop(file);

                /********************
                 * MENUCONTEXT OPEN *
                 ********************/
                browser_menu_context_open(file);

                /*********************
                 * DOUBLE CLICK ITEM *
                 *********************/
                browser_double_click_open(file);

                /********
                 * TEXT *
                 ********/
                pgTextWrap(name_file);
            }
            pgEndChildViewList();
        }
        pgEndViewList();
    }
}

void browser_double_click_open(FileDirFile *file)
{
    if (igIsItemHovered(0) && igIsMouseDoubleClicked(ImGuiMouseButton_Left))
    {
        switch (file->type)
        {
        case FILE_FOLDER:
            prChangeCurrentContentFolder(file->path, file->filename);
            break;
        }
    }
}

void browser_menu_context_open(FileDirFile *file)
{
    if (igIsItemClicked(ImGuiMouseButton_Right))
    {
        igOpenPopup_Str("browser-menu-context-file", 0);
    }

    if (igBeginPopupContextItem("browser-menu-context-file", ImGuiPopupFlags_MouseButtonRight))
    {
        igText("File ( %s )", file->name);
        igSeparator();

        if (igSelectable_Bool("Delete", false, 0, (ImVec2){0, 0}))
        {
        }
        if (igSelectable_Bool("Rename", false, 0, (ImVec2){0, 0}))
        {
        }
        igSeparator();
        if (igSelectable_Bool("Copy", false, 0, (ImVec2){0, 0}))
        {
        }
        if (igSelectable_Bool("Duplicate", false, 0, (ImVec2){0, 0}))
        {
        }

        if (file->type == FILE_FOLDER)
        {
            igSeparator();
            if (igSelectable_Bool(StringPrintf("Pegar... %s", file->name), false, 0, (ImVec2){0, 0}))
            {
            }
        }
        igEndPopup();
    }
}

void browser_drag_and_drop(FileDirFile *file)
{
    if (igBeginDragDropSource(0))
    {
        igSetDragDropPayload("browser_file_drag", file, sizeof(file), 0);
        igEndDragDropSource();
    }

    if (igBeginDragDropTarget())
    {
        ImGuiPayload *pay = igAcceptDragDropPayload("browser_file_drag", ImGuiDragDropFlags_SourceNoDisableHover);
        if (pay)
        {
            FileDirFile *drop = pay->Data;
            igEndDragDropTarget();
        }
    }
}