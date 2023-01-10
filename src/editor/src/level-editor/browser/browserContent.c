#include "browserContent.h"
#include "browserViewContent.h"

static gchar *path_project;
static gchar *path_project_content;
/*
 * Name: browserGetPathProject
 * Private
 * Params: (void)
 * Return: const gchar *
 * Desc: Obtenemos la ruta del proyecto
 */
const gchar *browserGetPathProject(void)
{
    return g_strdup(path_project);
}

/*
 * Name: browserInit
 * Private
 * Params: (void)
 * Return: const gchar *
 * Desc: Obtenemos la ruta del Content del proyecto
 */
const gchar *browserGetPathContent(void)
{
    return g_strdup(path_project_content);
}

/*
 * Name: browserInit
 * Private
 * Params: (const gchar *path_project)
 * Return: gboolean
 * Desc: Iniciamos el browser, para administrar
 * todos los archivos del proyecto.
 */
gboolean browserInit(const char *path_project)
{
    path_project = g_strdup(path_project);
    path_project_content = g_build_filename(path_project, "Content", NULL);

    return TRUE;
}