#include "browser.h"

GtkWidget *docked_browser(void)
{
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_margin_top(vbox, 5);
    gtk_widget_set_margin_start(vbox, 5);
    gtk_widget_set_margin_end(vbox, 5);

    GtkWidget *input_search = gtk_entry_new ();
    gtk_box_append(GTK_BOX(vbox), input_search);

    GtkWidget *list = gtk_icon_view_new();
    // GtkWidget *list = gtk_grid_view_new();
    gtk_box_append(GTK_BOX(vbox), list);

    return vbox;
}
