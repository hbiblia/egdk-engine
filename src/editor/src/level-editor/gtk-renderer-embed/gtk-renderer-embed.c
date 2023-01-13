#include <stdio.h>
#include <epoxy/gl.h>

#define SOKOL_IMPL
#define SOKOL_GLCORE33
#define SOKOL_EXTERNAL_GL_LOADER
#include "gtk-renderer-embed.h"

#include "rcamera.h"

struct _GtkSokolEmbed
{
    GtkWidget parent;
};

static guint _signals[SOKOL_SIGNALS] = {0};

G_DEFINE_TYPE_WITH_PRIVATE(GtkSokolEmbed, gtk_sokol_embed, GTK_TYPE_GL_AREA);

static void gtk_sokol_embed_class_init(GtkSokolEmbedClass *klass)
{
    GObjectClass *object_class = G_OBJECT_CLASS(klass);

    _signals[SOKOL_SIGNAL_INIT] = g_signal_new("sokol-init", G_TYPE_FROM_CLASS(klass),
                                               G_SIGNAL_RUN_FIRST | G_SIGNAL_NO_HOOKS,
                                               0, NULL, NULL,
                                               g_cclosure_marshal_VOID__VOID, G_TYPE_NONE, 0);

    _signals[SOKOL_SIGNAL_RENDER] = g_signal_new("sokol-render", G_TYPE_FROM_CLASS(klass),
                                                 G_SIGNAL_RUN_LAST | G_SIGNAL_NO_HOOKS,
                                                 0, NULL, NULL,
                                                 g_cclosure_marshal_VOID__FLOAT, G_TYPE_NONE, 1, G_TYPE_FLOAT);

    _signals[SOKOL_SIGNAL_SHUTDOWN] = g_signal_new("sokol-shutdown", G_TYPE_FROM_CLASS(klass),
                                                   G_SIGNAL_RUN_LAST | G_SIGNAL_NO_HOOKS,
                                                   0, NULL, NULL,
                                                   g_cclosure_marshal_VOID__VOID, G_TYPE_NONE, 0);

    _signals[SOKOL_SIGNAL_RESIZE] = g_signal_new("sokol-resize", G_TYPE_FROM_CLASS(klass),
                                                 G_SIGNAL_RUN_LAST | G_SIGNAL_NO_HOOKS,
                                                 0, NULL, NULL,
                                                 g_cclosure_marshal_VOID__VOID, G_TYPE_NONE, 0);
}

static gboolean tick(GtkWidget *widget, GdkFrameClock *frame_clock, gpointer data)
{
    GdkFrameTimings *timings, *pv_timings;
    gint64 pv_frame_time = 0, frame_time, last_frame_time;
    gint64 history_start, history_len;
    gint64 frame;

    GtkSokolEmbedPrivate *priv = gtk_sokol_embed_get_instance_private(GTK_SOKOL_EMBED(widget));

    frame = gdk_frame_clock_get_frame_counter(frame_clock);
    frame_time = gdk_frame_clock_get_frame_time(frame_clock);

    gtk_widget_queue_draw(widget);

    history_start = gdk_frame_clock_get_history_start(frame_clock);

    if (frame % priv->fpsLimit == 0)
    {
        history_len = frame - history_start;
        if (history_len > 0)
        {
            pv_timings = gdk_frame_clock_get_timings(frame_clock, frame - history_len);
            pv_frame_time = gdk_frame_timings_get_frame_time(pv_timings);
            priv->fpsStat = (G_USEC_PER_SEC * history_len) / (double)(frame_time - pv_frame_time);
        }
    }

    guint64 current_time = g_get_monotonic_time();
    priv->g_Time = current_time;
    gfloat delta = ((gfloat)(current_time - priv->g_Time) / 1000000);

    timings = gdk_frame_clock_get_current_timings(frame_clock);
    pv_timings = gdk_frame_clock_get_timings(frame_clock, gdk_frame_timings_get_frame_counter(timings) - 1);

    if (pv_timings != NULL)
        pv_frame_time = gdk_frame_timings_get_frame_time(pv_timings);

    priv->delta = delta;
    g_print("BB: %f\n", priv->delta);

    return G_SOURCE_CONTINUE;
}

static void gtk_sokol_embed_init(GtkSokolEmbed *embed)
{
    GtkSokolEmbedPrivate *priv = gtk_sokol_embed_get_instance_private(embed);

    priv->fpsLimit = 30;
    priv->bInit = FALSE;
    priv->g_Time = 0;
    priv->delta = 0;

    gtk_widget_add_tick_callback(GTK_WIDGET(embed), tick, embed, NULL);
}

static void realize(GtkSokolEmbed *embed, gpointer data)
{
    gtk_gl_area_make_current(GTK_GL_AREA(embed));
    if (gtk_gl_area_get_error(GTK_GL_AREA(embed)) != NULL)
        return;
}

static void unrealize(GtkSokolEmbed *embed, gpointer data)
{
    gtk_gl_area_make_current(GTK_GL_AREA(embed));
    if (gtk_gl_area_get_error(GTK_GL_AREA(embed)) != NULL)
        return;

    g_signal_emit(embed, _signals[SOKOL_SIGNAL_SHUTDOWN], 0, embed);

    renderer_shutdown();
}

static void resize(GtkSokolEmbed *embed, gint width, gint height, gpointer data)
{
    if (gtk_gl_area_get_error(GTK_GL_AREA(embed)) != NULL)
        return;

    GtkSokolEmbedPrivate *priv = gtk_sokol_embed_get_instance_private(embed);

    priv->width = width;
    priv->height = height;

    //
    // Sokol no se inicia bien cuando se carga en el realize,
    // encontre que se carga bien cuando procesa el resize.
    //
    if (priv->bInit == FALSE)
    {
        priv->bInit = TRUE;
        renderer_init();
        g_signal_emit(embed, _signals[SOKOL_SIGNAL_INIT], 0, embed);
    }

    renderer_resize(width, height);
    rcamera_active_set_size(width, height);

    g_signal_emit(embed, _signals[SOKOL_SIGNAL_RESIZE], 0, embed);
}

static gboolean render(GtkSokolEmbed *embed, gpointer data)
{
    if (gtk_gl_area_get_error(GTK_GL_AREA(embed)) != NULL)
        return FALSE;

    rcamera_begin();
    {
        gfloat delta = gtk_sokol_embed_get_delta(embed);
        g_signal_emit(embed, _signals[SOKOL_SIGNAL_RENDER], 0, delta);
    }
    rcamera_end();

    renderer_frame();
    glFlush();

    return TRUE;
}

GtkSokolEmbed *gtk_sokol_embed_new(void)
{
    GtkSokolEmbed *embed = g_object_new(GTK_TYPE_SOKOL_EMBED, NULL);
    gtk_gl_area_set_required_version(GTK_GL_AREA(embed), 3, 3);
    gtk_widget_set_focus_on_click(GTK_WIDGET(embed), TRUE);
    gtk_widget_set_focusable(GTK_WIDGET(embed), TRUE);
    gtk_widget_set_vexpand(GTK_WIDGET(embed), TRUE);
    gtk_widget_set_hexpand(GTK_WIDGET(embed), TRUE);

    g_signal_connect(embed, "render", G_CALLBACK(render), NULL);
    g_signal_connect(embed, "resize", G_CALLBACK(resize), NULL);
    g_signal_connect(embed, "unrealize", G_CALLBACK(unrealize), NULL);
    g_signal_connect(embed, "realize", G_CALLBACK(realize), NULL);

    return embed;
}

gint gtk_sokol_embed_get_width(GtkSokolEmbed *embed)
{
    GtkSokolEmbedPrivate *priv = gtk_sokol_embed_get_instance_private(embed);
    return priv->width;
}

gint gtk_sokol_embed_get_height(GtkSokolEmbed *embed)
{
    GtkSokolEmbedPrivate *priv = gtk_sokol_embed_get_instance_private(embed);
    return priv->height;
}

void gtk_sokol_embed_set_fps_limit(GtkSokolEmbed *embed, gint fps)
{
    GtkSokolEmbedPrivate *priv = gtk_sokol_embed_get_instance_private(embed);
    priv->fpsLimit = fps < 25 ? 30 : fps;
}

gfloat gtk_sokol_embed_get_delta(GtkSokolEmbed *embed)
{
    GtkSokolEmbedPrivate *priv = gtk_sokol_embed_get_instance_private(embed);
    return priv->delta;
}

gint gtk_sokol_embed_get_fps_stat(GtkSokolEmbed *embed)
{
    GtkSokolEmbedPrivate *priv = gtk_sokol_embed_get_instance_private(embed);
    return priv->fpsStat;
}
