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

BrowserView *browser_view_new(const gchar *name, const GdkPixbuf *image)
{
    BrowserView *b = g_object_new(browser_view_get_type(), NULL);
    b->name = g_strdup(name);
    b->image = image;
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
