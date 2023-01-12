#include "viewport.h"
#include <math.h>
#include <gtk/gtk.h>
#include "renderer/renderer.h"
#include "renderer/rcamera.h"
#include "renderer/rshape.h"
#include "renderer/rtransform.h"

static gint64 g_Time;
static float delta;

static gboolean tick(GtkWidget *widget, GdkFrameClock *frame_clock, gpointer data)
{
    GdkFrameTimings *timings, *pv_timings;
    gint64 pv_frame_time = 0, frame_time, last_frame_time;
    gint64 history_start, history_len;
    gint64 frame;

    frame = gdk_frame_clock_get_frame_counter(frame_clock);
    frame_time = gdk_frame_clock_get_frame_time(frame_clock);

    gtk_widget_queue_draw(widget);

    history_start = gdk_frame_clock_get_history_start(frame_clock);

    // Limit FPS
    if (frame % 60 == 0)
    {
        history_len = frame - history_start;
        if (history_len > 0)
        {
            pv_timings = gdk_frame_clock_get_timings(frame_clock, frame - history_len);
            pv_frame_time = gdk_frame_timings_get_frame_time(pv_timings);
            gchar *s = g_strdup_printf("FPS: %-4.1f", (G_USEC_PER_SEC * history_len) / (double)(frame_time - pv_frame_time));
            // gtk_label_set_label(fps_label, s);
            g_free(s);
        }
    }

    guint64 current_time = g_get_monotonic_time();
    delta = ((float)(current_time - g_Time) / 1000000);
    g_Time = current_time;

    timings = gdk_frame_clock_get_current_timings(frame_clock);
    pv_timings = gdk_frame_clock_get_timings(frame_clock, gdk_frame_timings_get_frame_counter(timings) - 1);

    if (pv_timings != NULL)
        pv_frame_time = gdk_frame_timings_get_frame_time(pv_timings);

    return G_SOURCE_CONTINUE;
}

static rtransform t;
static gboolean render(GtkGLArea *area, GdkGLContext *context)
{
    t.rotation.z += 1.0f * delta;

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

    t = new_Transform;
    rcamera_active_set_default();

    gtk_widget_add_tick_callback(GTK_WIDGET(area), tick, area, NULL);
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
