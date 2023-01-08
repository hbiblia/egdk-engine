#include "viewport.h"
#include <math.h>
#include <gtk/gtk.h>
#include <epoxy/gl.h>

static gboolean render(GtkGLArea *area, GdkGLContext *context)
{
    glClearColor(0,0,0,1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
    return TRUE;
}

static void resize(GtkGLArea *area, gint width, gint height, gpointer data)
{
    g_print("Size: %d,%d\n", width, height);
}

GtkWidget *docked_viewport(void)
{
    GtkWidget *docked = gtk_gl_area_new();
    g_signal_connect(docked, "render", G_CALLBACK(render), NULL);
    g_signal_connect(docked, "resize", G_CALLBACK(resize), NULL);

    return docked;
}