#include "viewport.h"
#include <math.h>
#include <gtk/gtk.h>

#include "../gtk-renderer-embed/gtk-renderer-embed.h"
#include "renderer.h"
#include "rcamera.h"
#include "rshape.h"
#include "rtransform.h"

static rtransform t;
static void on_sokol_render(gfloat delta)
{
    t.rotation.z += 1.0f * delta;
    rshape_draw_rectangle(&(rshape_desc){.t = t, .w = 100, .h = 100, .color = {150, 0, 150, 255}});
}

static void on_sokol_init(GtkGLArea *area, gpointer user_data)
{
    t = new_Transform;
}

GtkWidget *docked_viewport(void)
{
    GtkWidget *docked = gtk_sokol_embed_new();
    g_signal_connect(docked, "sokol-init", G_CALLBACK(on_sokol_init), NULL);
    g_signal_connect(docked, "sokol-render", G_CALLBACK(on_sokol_render), NULL);

    return docked;
}
