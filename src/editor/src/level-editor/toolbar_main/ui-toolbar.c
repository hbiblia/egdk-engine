
#include "toolbar.h"

GtkWidget *ui_toolbar(void)
{
    GtkWidget *headerbar = gtk_header_bar_new();

    GtkWidget *btn_save = gtk_button_new_with_label("Save");
    gtk_header_bar_pack_start(GTK_HEADER_BAR(headerbar), btn_save);

    return headerbar;
}