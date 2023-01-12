#ifndef FILE_FN_H
#define FILE_FN_H
#include <stdio.h>
#include <glib.h>

/*
 * Name: FileIsExtension
 * Private
 * Params: (const gchar *filename)
 * Return: gboolean
 * Desc: Comprobamos si un filename tiene la ext
 */
gboolean FileIsExtension(const gchar *filename, const gchar *ext);

/*
 * Name: FileGetExtension
 * Private
 * Params: (const gchar *filename)
 * Return: const gchar *
 * Desc: Obtenemos la ext de un archivo
 */
const gchar *FileGetExtension(const gchar *filename);

#endif