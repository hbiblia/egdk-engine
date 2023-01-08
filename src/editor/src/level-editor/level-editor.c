
#include "level-editor.h"
#include "toolbar_main/toolbar.h"
#include "viewport/viewport.h"
#include "browser/browser.h"
#include "tiled/tiled.h"

void level_editor_ui(GtkApplication *app)
{
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Level Editor");
    gtk_window_set_default_size(GTK_WINDOW(window), 1280, 720);

    GtkWidget *headerbar = ui_toolbar();
    gtk_window_set_titlebar(GTK_WINDOW(window), headerbar);

    // ------------------------------------
    // docked main content [no dinamico]
    // ------------------------------------
    GtkWidget *panedMain = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_paned_set_resize_start_child(GTK_PANED(panedMain), FALSE);
    gtk_paned_set_shrink_start_child(GTK_PANED(panedMain), FALSE);
    gtk_window_set_child(GTK_WINDOW(window), panedMain);

    GtkWidget *notebook = gtk_notebook_new();
    gtk_widget_set_size_request(GTK_WIDGET(notebook), 300, -1);
    gtk_paned_set_start_child(panedMain, notebook);
    {
        GtkWidget *browser = docked_browser();
        gtk_notebook_append_page(GTK_NOTEBOOK(notebook), browser, gtk_label_new("Browser"));

        GtkWidget *tiled = docked_tiled();
        gtk_notebook_append_page(GTK_NOTEBOOK(notebook), tiled, gtk_label_new("Tiled"));
    }

    GtkWidget *viewport = docked_viewport();
    gtk_paned_set_end_child(panedMain, viewport);

    gtk_window_present(GTK_WINDOW(window));
}