#include "browserViewFileType.h"

G_DEFINE_TYPE(BrowserView, browser_view, G_TYPE_OBJECT)

static void browser_view_finalize(GObject *object)
{
    BrowserView *self = BROWSER_VIEW(object);
    g_free(self->name);
    G_OBJECT_CLASS(browser_view_parent_class)->finalize(object);
}

static void browser_view_class_init(BrowserViewClass *klass)
{
    GObjectClass *object_class = G_OBJECT_CLASS(klass);
    object_class->finalize = browser_view_finalize;
}

static void browser_view_init(BrowserView *self)
{
}

static BrowserView *browser_view_new(const gchar *name, const gchar *filename)
{
    BrowserView *b = g_object_new(browser_view_get_type(), NULL);
    b->name = g_strdup(name);
    // TODO: Cambiar en la proxima version, hacer esto fuera.
    b->image = gdk_pixbuf_new_from_file_at_scale(filename, 64, 64, TRUE, NULL);
    return b;
}

const GdkPixbuf *browser_view_app_get_icon(BrowserView *view)
{
    return view->image;
}

const gchar *browser_view_app_get_name(BrowserView *view)
{
    return g_strdup(view->name);
}

GListStore *browser_view_get_content(void)
{
    GListStore *store = g_list_store_new(browser_view_get_type());

    g_list_store_append(store, browser_view_new("Pokemon","bin/JG_Color.png"));
    g_list_store_append(store, browser_view_new("Pika Pika","bin/JG_Color.png"));
    g_list_store_append(store, browser_view_new("StartBolita","bin/JG_Color.png"));

    return store;
}