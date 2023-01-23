#ifndef _EDITOR_BROWSER_H
#define _EDITOR_BROWSER_H
#include <stdio.h>
#include <glib.h>

gint browser_view_list_func_sorty(gconstpointer a, gconstpointer b);

GPtrArray *browser_list_dir_content(const char *path);

void browser_home_path(void);
void browser_move_back_path(void);

#endif
