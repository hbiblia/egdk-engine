#ifndef WIDGET_SOKOL_GL_H
#define WIDGET_SOKOL_GL_H

// GTK4
#include <gtk/gtk.h>
#include "renderer.h"

G_BEGIN_DECLS

typedef struct _GtkSokolEmbedPrivate GtkSokolEmbedPrivate;

#define GTK_TYPE_SOKOL_EMBED gtk_sokol_embed_get_type()
G_DECLARE_FINAL_TYPE(GtkSokolEmbed, gtk_sokol_embed, GTK, SOKOL_EMBED, GtkGLArea)

typedef enum
{
    SOKOL_SIGNAL_INIT = 0,
    SOKOL_SIGNAL_RENDER,
    SOKOL_SIGNAL_SHUTDOWN,
    SOKOL_SIGNAL_RESIZE,
    SOKOL_SIGNALS
}SokolEmbedSignal;

struct _GtkSokolEmbedPrivate
{
    GtkWidget parent_instance;
    gboolean bInit;
    gint width;
    gint height;
    gint fpsLimit;
    guint g_Time;
    gfloat delta;
    gint fpsStat;
};

GtkSokolEmbed *gtk_sokol_embed_new(void);
void gtk_sokol_embed_set_fps_limit(GtkSokolEmbed *embed, gint fps);
gint gtk_sokol_embed_get_height(GtkSokolEmbed *embed);
gint gtk_sokol_embed_get_width(GtkSokolEmbed *embed);
gfloat gtk_sokol_embed_get_delta(GtkSokolEmbed *embed);
gint gtk_sokol_embed_get_fps_stat(GtkSokolEmbed *embed);

G_END_DECLS

#endif