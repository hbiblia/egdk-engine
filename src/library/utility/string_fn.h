#ifndef STRING_FN_H
#define STRING_FN_H
#include <stdio.h>
#include <stdbool.h>

/*
 * Name: StringReplace
 * Desc: Remplazamos un string por otro string
 */
char *StringReplace(const char *str, const char *find, const char *replace);

/*
 * Name: String
 * Desc: Duplica un string
 */
char *String(const char *str);

/*
 * Name: StringPrintf
 * Desc:
 */
char *StringPrintf(const char *format, ...);

/*
 * Name: StringSplit
 * Desc: Separa un string
 */
char **StringSplit(const char *string, const char *delimiter);

/*
 * Name: StringSplitFree
 * Desc: Limpia el resultado de StringSplit
 */
void StringSplitFree(char **split);

/*
 * Name: StringMatch
 * Desc: Comprueba si una búsqueda realizada para debe coincidir
 */
bool StringMatch(const char *search, const char *hit);

#endif