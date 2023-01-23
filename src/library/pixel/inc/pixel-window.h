#ifndef _PIXEL_WINDOW_H
#define _PIXEL_WINDOW_H
#include "pixel.h"

/**
 * pixel_event
 *
 * administramos los eventos que se reproducen en la ventana
 *
 */

typedef struct pixel_event_t
{
    void *event;
}pixel_event_t;

/**
 * pixel_window_desc
 *
 *
 */
typedef struct pixel_window_desc
{
    void (*init_fn)(void);                 //
    void (*draw_fn)(float dt);             //
    void (*event_fn)(const pixel_event_t *); //
    void (*shutdown_fn)(void);             //

    const char *title; // Titulo de la ventana
} pixel_window_desc;

void pixel_window_main(const pixel_window_desc *desc);

int pixel_window_width(void);

int pixel_window_height(void);

double pixel_window_delta_time(void);

uint64_t pixel_window_frame_count(void);

float pixel_window_dpi_scale(void);

#endif