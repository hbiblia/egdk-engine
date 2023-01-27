#include <glib.h>
#include "utility/string_fn.h"
#include <stdarg.h>
#include <string.h>

/*
 * Name: StringReplace
 * Public
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

/*
 * Name: String
 * Public
 * Params: (const char *str)
 * Return: char *
 * Desc: Duplica un string
 */
char *String(const char *str)
{
    return g_strdup(str);
}

/*
 * Name: StringPrintf
 * Public
 * Params: (const char *format)
 * Return: char *
 * Desc: Duplica un string con format
 */
char *StringPrintf(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    char *v = g_strdup_vprintf(format, args);
    va_end(args);
    return v;
}

/*
 * Name: StringSplit
 * Public
 * Params: (const char *string, const char *delimiter)
 * Return: char *
 * Desc: Separa un string
 */
char **StringSplit(const char *string, const char *delimiter)
{
    return g_strsplit(string, delimiter, -1);
}

/*
 * Name: StringSplitFree
 * Public
 * Params: (char **str)
 * Return: void
 * Desc: Limpia el resultado de StringSplit
 */
void StringSplitFree(char **split)
{
    g_strfreev(split);
}

/*
 * Name: StringMatch
 * Public
 * Params: (const char *search, const char *hit)
 * Return: bool
 * Desc: Comprueba si una búsqueda realizada para debe coincidir
 */
bool StringMatch(const char *search, const char *hit)
{
    return g_str_match_string(search, hit, FALSE);
}