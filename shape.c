#include "shape.h"

Shape* shape_new()
{
	Shape* shp;
	shp = (Shape*)malloc(sizeof(Shape));
	return shp;
}

void shape_set_type(Shape * shp, ShapeType type)
{
	assert(shp);
	assert(type);
	assert(type >= NO_SHAPE && type <= T_SHAPE);
	shp->type =  type;
}

void shape_set_coordinate(Shape *shp, Point pt, int index)
{
	assert(shp);
	assert(pt);
	assert(index >= 0 && index <=3);
	shp->coords[index] = pt;
}

int shape_get_x_coordinate(Shape *shp, int index)
{
	return shp->coords[i].x;
}

int shape_get_y_coordinate(Shape *shp, int index)
{
	return shp->coords[i].y;
}

int shape_max_x(Shape *shp)
{
	int m = shp->coords[0].x;
	for(int i = 0; i < 4; i++)	
	{
		m = max(m, shp->coords[i].x);
	}
	return m;
}

int shape_max_y(Shape *shp)
{
	int m = shp->coords[0].y;
	for(int i = 0; i < 4; i++)
	{
		m = max(m, shp->coords[i].y);
	}
	return m;
}

int shape_min_x(Shape *shp)
{
	int m = shp->coords[0].x;
	for(int i = 0; i < 4; i++)
	{
		m = min(m, shp->coords[i].x);
	}
	return m;
}

int shape_min_y(Shape *shp)
{
	int m = shp->coords[0].y;
	for(int i = 0; i < 4; i++)
	{
		m = min(m, shp->coords[i].y);
	}
	return m;
}

Shape* shape_random_new()
{
	Shape * shape;
	shape = shape_new();
	int type = rand() % 7 +1;
	shape_set_type(shape, ShapeType(type));
	
	return shape;
}

void shape_rotate_left(shape *shp)
{
	if(shp->type == SQUARE_SHP)
		return;
	for(int i = 0; i < 4; i++)
	{
		int x = shp->coords[i].x;
		int y = shp->coords[i].y;
		shp->coords[i].x = -y;
		shp->coords[i].y = x;
	}
}

void shape_rotate_right(shape *shp)
{
	if(shp->type == SQUARE_SHP)
		return;
	
	for(int i = 0; i < 4; i++)
	{
		int x = shp->coords[i].x;
		int y = shp->coords[i].y;
		shp->coords[i].x = y;
		shp->coords[i].y = -x;
	}
}
