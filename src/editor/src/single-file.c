#include "single-file.h"
#include "pixel/pixel-ecs.h"
#include <glib.h>

static EditorSingleFile *sfile;

void eSingleFile_Init(void)
{
    sfile = g_new0(EditorSingleFile, 1);
    sfile->entity_selected = pEcs_EntityRoot();
}

void eSingleFile_Shutdown(void)
{
    g_free(sfile);
}

EditorSingleFile *eSingleFile_Get(void)
{
    return sfile;
}
