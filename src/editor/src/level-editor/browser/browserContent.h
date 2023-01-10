#ifndef BROWSER_CONTENT_H
#define BROWSER_CONTENT_H
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

#define BROWSER_GET_PATH_CONTENT browserGetPathContent()

const gchar *browserGetPathProject(void);

const gchar *browserGetPathContent(void);

gboolean browserInit(const char *path_project);

#endif