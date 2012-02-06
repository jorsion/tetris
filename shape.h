#ifndef TETRIS_SHAPE_H
#define TETRIS_SHAPE_H

typedef struct _point
{
	int x;
	int y;
} point;

enum SHAPE_TYPE
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

typedef struct _shape
{
	SHAPE_TYPE type;
	point coordinates[4];
} shape;

shape * shape_new();

void shape_set_type(shape *shp, SHAPE_TYPE type);

void shape_set_coordinate(shape *shp, point pt, int index);

int shape_max_x(shape *shp);

int shape_max_y(shape *shp);

int shape_min_x(shape *shp);

int shape_min_y(shape *shp);

int shape_rotate_left(shape *shp);

int shape_rotate_right(shape *shp);

#endif
