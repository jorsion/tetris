#ifndef TETRIS_GRAPH_H
#define TETRIS_GRAPH_H

#include <cairo.h>

typedef struct _color Color;

struct _color
{
	char red;
	char green;
	char blue;
};

void graph_set_color(cairo_t *cr, Color color);

void graph_set_line_width(cairo_t *cr, int lineWidth);

void graph_draw_line(cairo_t *cr, int x1, int y1, int y2, int y3);

void graph_draw_rectangle(cairo_t *cr, int x, int y, int width, int height, Color lineColor, Color areaColor);

#endif
