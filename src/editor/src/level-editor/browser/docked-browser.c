#include "browser.h"
#include "browserViewFileType.h"
#include "browserViewContent.h"

// TODO:
// [-] Quitar la autoSelection
// [-] Cargar los archivos del proyecto
// [-] Implementar el buscador o filtro
// [-] Drag and Drop (Viewport)
// [-] Sqlite3 referencia de elementos.
// ** Etapa 2 **
// [-] Drag and Drop (Folder)
// [-] Crea Folder
// [-] Borrar y crear archivos
// [-] Importar contenido
// [-] Menu flotante o context-menu
// [-] Cambiar entre tipos de vista (icon, list)


/*
 *  GTK_?_DRAG AND DROP
 *
 *
 */

static void on_drag_begin(GtkDragSource *source, GdkDrag *drag, gpointer data)
{
    g_print("DragBegin\n");
    GdkPaintable *paint = gtk_widget_paintable_new(GTK_WIDGET(data));
    gtk_drag_source_set_icon(source, paint, 0, 0);
    g_object_unref(paint);
}

static GdkContentProvider *on_drag_prepare(GtkDragSource *source, double x, double y, gpointer data)
{
    g_print("DragPrepare\n");

    GFile *file = NULL;

    return gdk_content_provider_new_union((GdkContentProvider*[1]){
        gdk_content_provider_new_typed(G_TYPE_FILE, file),
    },1);
}

/*
 *  GTK_?_VIEW_MODEL
 *
 *
 */

static GListModel *_grid_view_model()
{
    // Este es temporal, cuando tengamos la forma de cargar un proyecto se movera.
    browserInit("D:/Github/egdk-engine/examples/sprites");

    GListStore *store = g_list_store_new(browser_view_get_type());
    browserViewContentDirCurrentPath(store, "");

    return G_LIST_MODEL(store);
}

/*
 *  GTK_?_VIEW_NEW FACTORY
 *
 *
 */

static void _factory_setup(GtkListItemFactory *factory, GtkListItem *list_item)
{
    GtkWidget *box;
    GtkWidget *image;
    GtkWidget *label;

    box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 12);

    image = gtk_image_new();
    gtk_image_set_icon_size(GTK_IMAGE(image), GTK_ICON_SIZE_LARGE);
    gtk_box_append(GTK_BOX(box), image);

    label = gtk_label_new("");
    gtk_label_set_width_chars(GTK_LABEL(label), 10);
    gtk_label_set_wrap(GTK_LABEL(label), TRUE);
    gtk_label_set_wrap_mode(GTK_LABEL(label), PANGO_WRAP_WORD);
    gtk_box_append(GTK_BOX(box), GTK_LABEL(label));

    GtkDragSource *drags = gtk_drag_source_new();
    g_signal_connect(drags, "drag-begin", G_CALLBACK(on_drag_begin), image);
    g_signal_connect(drags, "prepare", G_CALLBACK(on_drag_prepare), image);
    gtk_widget_add_controller(GTK_WIDGET(box), GTK_EVENT_CONTROLLER(drags));

    gtk_list_item_set_child(list_item, box);
}

static void _factory_bind(GtkListItemFactory *factory, GtkListItem *list_item)
{
    GtkWidget *image;
    GtkWidget *label;

    BrowserView *view = gtk_list_item_get_item(list_item);

    image = gtk_widget_get_first_child(gtk_list_item_get_child(list_item));
    label = gtk_widget_get_next_sibling(image);

    gtk_image_set_from_pixbuf(GTK_IMAGE(image), browser_view_app_get_icon(view));

    gtk_label_set_label(GTK_LABEL(label), browser_view_app_get_name(view));
}

static GtkListItemFactory *_grid_view_factory()
{
    GtkListItemFactory *factory = gtk_signal_list_item_factory_new();
    g_signal_connect(factory, "setup", G_CALLBACK(_factory_setup), NULL);
    g_signal_connect(factory, "bind", G_CALLBACK(_factory_bind), NULL);

    return factory;
}

static void _search_entry(GtkSearchEntry *self, GListModel *model)
{
    const gchar *search = gtk_editable_get_text(self);
    browserViewContentDirCurrentPath(model, search);
}

GtkWidget *docked_browser(void)
{
    GListModel *model;

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_margin_top(vbox, 5);
    gtk_widget_set_margin_start(vbox, 5);
    gtk_widget_set_margin_end(vbox, 5);

    GtkWidget *input_search = gtk_search_entry_new();
    gtk_box_append(GTK_BOX(vbox), input_search);

    GtkWidget *scrolled = gtk_scrolled_window_new();
    gtk_widget_set_margin_top(scrolled, 5);
    gtk_widget_set_hexpand(scrolled, TRUE);
    gtk_widget_set_vexpand(scrolled, TRUE);
    gtk_box_append(GTK_BOX(vbox), scrolled);
    {
        model = _grid_view_model();
        GtkSingleSelection *s = gtk_single_selection_new(model);
        gtk_single_selection_set_autoselect(s, TRUE);

        GtkWidget *list = gtk_list_view_new(s, _grid_view_factory());
        gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled), list);

        // GtkDragSource *drags = gtk_drag_source_new();
        // g_signal_connect(drags, "drag-begin", G_CALLBACK(on_drag_begin), list);
        // g_signal_connect(drags, "prepare", G_CALLBACK(on_drag_prepare), list);
        // gtk_widget_add_controller(GTK_WIDGET(list), GTK_EVENT_CONTROLLER(drags));
    }

    g_signal_connect(input_search, "search-changed", G_CALLBACK(_search_entry), model);

    return vbox;
}
