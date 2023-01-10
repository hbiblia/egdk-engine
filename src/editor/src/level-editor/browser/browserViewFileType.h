
/*
 *  GTYPE::BrowserView
 *
 *
 */

#pragma once

#include <gtk/gtk.h>

G_DECLARE_FINAL_TYPE(BrowserView, browser_view, BROWSER, VIEW, GObject)

struct _BrowserView
{
    GObject parent;
    gchar *name;
    GdkPixbuf *image;
};

struct _BrowserViewClass
{
    GObjectClass parent_class;
};

BrowserView *browser_view_new(const gchar *name, const GdkPixbuf *image);

const GdkPixbuf *browser_view_app_get_icon(BrowserView *view);

const gchar *browser_view_app_get_name(BrowserView *view);