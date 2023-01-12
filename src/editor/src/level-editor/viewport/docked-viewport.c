#include "viewport.h"
#include <math.h>
#include <gtk/gtk.h>
#include "renderer/renderer.h"
#include "renderer/rcamera.h"
#include "renderer/rshape.h"
#include "renderer/rtransform.h"

static gboolean render(GtkGLArea *area, GdkGLContext *context)
{
    rtransform t = new_Transform;
    t.rotation.z += 1.0f;

    rcamera_begin();
    {
        rshape_draw_rectangle(&(rshape_desc){.t = t, .w = 100, .h = 100, .color = {150, 0, 150, 255}});
    }
    rcamera_end();

    renderer_frame();
    glFlush();
    return TRUE;
}

static void resize(GtkGLArea *area, gint width, gint height, gpointer data)
{
    gtk_gl_area_make_current(area);
    if (gtk_gl_area_get_error(area) != NULL)
        return;

    renderer_resize(width, height);
    rcamera_active_set_size(width, height);
}

static void realize(GtkGLArea *area, gpointer user_data)
{
    gtk_gl_area_make_current(area);

    if (gtk_gl_area_get_error(GTK_GL_AREA(area)) != NULL)
        return;

    rcamera_active_set_default();
}

static void unrealize(GtkGLArea *area, gpointer user_data)
{
    renderer_shutdown();
}

GtkWidget *docked_viewport(void)
{
    GtkWidget *docked = gtk_gl_area_new();
    gtk_gl_area_set_required_version(GTK_GL_AREA(docked), 3, 3);
    g_signal_connect(docked, "render", G_CALLBACK(render), NULL);
    g_signal_connect(docked, "resize", G_CALLBACK(resize), NULL);
    g_signal_connect(docked, "realize", G_CALLBACK(realize), NULL);
    g_signal_connect(docked, "unrealize", G_CALLBACK(unrealize), NULL);

    return docked;
}
