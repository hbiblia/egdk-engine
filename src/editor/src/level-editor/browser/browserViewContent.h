#ifndef BROWSER_VIEW_CONTENT_H
#define BROWSER_VIEW_CONTENT_H
#include "browser.h"

typedef enum
{
    BROWSER_FILE_NULL = 0,
    BROWSER_FILE_EMPTY,
    BROWSER_FILE_T_FOLDER,
    BROWSER_FILE_T_TEXTURE,
    BROWSER_FILE_T_TILED,
    BROWSER_FILE_T_LUA,
    BROWSER_FILE_T_JSON,
    BROWSER_FILE_LAST
} BrowserFileType;

char *browserViewContentStringReplace(const char *str, const char *find, const char *replace);

char *browserViewContentPathNormalize(const char *path);

gboolean browserViewContentFileIsExt(const gchar *filename, const gchar *ext);

const gchar *browserViewContentFileGetExt(const gchar *filename);

gboolean browserViewContentInit(const char *path_project);

void browserViewContentDirCurrentPath(GListStore *store, const gchar *filter);

void browserViewContentSetPathCurrent(const gchar *path);

void browserViewContentClear(GListStore *store);

void browserViewContentAppend(GListStore *store, const char *name, const GdkPixbuf *image);

#endif