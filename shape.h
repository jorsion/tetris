#ifndef TETRIS_SHAPE_H
#define TETRIS_SHAPE_H

typedef struct _Point Point;

typedef struct _Shape Shape;

struct _Point
{
	int x;
	int y;
};

enum ShapeType
{
	NO_SHAPE = 0,
	Z_SHAPE,
	S_SHAPE,
	L_SHAPE,
	MIRROR_L_SHAPE,
	LINE_SHAPE,
	SQUARE_SHAPE,
	T_SHAPE
};

struct _Shape
{
	SHAPE_TYPE type;
	Point coords[4];
};

Shape * shape_new();

void shape_set_type(Shape *shp, ShapeType type);

void shape_set_coordinate(Shape *shp, Point pt, int index);

int shape_max_x(Shape *shp);

int shape_max_y(Shape *shp);

int shape_min_x(Shape *shp);

int shape_min_y(Shape *shp);

void shape_rotate_left(Shape *shp);

void shape_rotate_right(Shape *shp);

Shape *shape_random_new();

#endif
