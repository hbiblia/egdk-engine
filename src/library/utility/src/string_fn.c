#include "string_fn.h"

/*
 * Name: StringReplace
 * Private
 * Params: (const char *str, const char *find, const char *replace)
 * Return: char *
 * Desc: Remplazamos un string por otro string
 */
char *StringReplace(const char *str, const char *find, const char *replace)
{
    GString *gstr = g_string_new(str);
    g_string_replace(gstr, find, replace, 0);
    return g_string_free(gstr, FALSE);
}