#include "graph.h"

void graph_set_color(cairo_t *cr, Color color)
{
	cairo_set_source_rgb(cr, color.red, color.green, color.blue);
}

void graph_set_line_width(cairo_t *cr, int lineWidth)
{
	cairo_set_line_width(cr, lineWidth);
}

void graph_draw_line(cairo_t *cr, int x1, int y1, int x2, int y2)
{
	cairo_move_to(cr, x1, y1);
	cairo_line_to(cr, x2, y2);
	cairo_stroke(cr);
}

void graph_draw_rectangle(cairo_t *cr, int x, int y, int width, int height, Color lineColor, Color areaColor)
{
	graph_set_color(cr, lineColor);
	graph_set_line_width(cr, 1);
	
	cairo_rectangle(cr, x, y, width, height);
	cairo_stroke_preserve(cr);

	graph_set_color(cr, areaColor);
	cairo_fill(cr);
}
