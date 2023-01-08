
/*
 *
 *
 *
 *
 */

#include <stdio.h>
#include <gtk/gtk.h>
#include "level-editor/level-editor.h"

static void on_activate(GtkApplication *app)
{
    level_editor_ui(app);
}

int main(int argc, char *argv[])
{
    GtkApplication *app = gtk_application_new("com.egdk.egdkengine",
                                              G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(on_activate), NULL);
    return g_application_run(G_APPLICATION(app), argc, argv);
}