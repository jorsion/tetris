#include <assert.h>
#include "shape.h"

int coordsTable[8][4][2] =
{
	{	
		{0, 0}, {0, 0}, {0, 0}, {0, 0}
	},
	{
		{0, -1}, {0, 0}, {-1, 0}, {-1, 1}
	},
	{
		{0, -1}, {0, 0}, {1, 0}, {1, 1}
	},
	{
		{0, -1}, {0, 0}, {0, 1}, {0, 2}
	},
	{
		{-1, 0}, {0, 0}, {1, 0}, {0, 1}
	},
	{
		{0, 0}, {1, 0}, {0, 1}, {1, 1}
	},
	{	
		{-1, -1}, {0, -1}, {0, 0}, {0, 1}
	},
	{
		{10, -10}, {0, -10}, {0, 0}, {0, 10}
	}
};

Shape* shape_new()
{
	Shape* shp;
	shp = (Shape*)malloc(sizeof(Shape));
	shape_set_random_type(shp);
	return shp;
}

void shape_set_type(Shape * shp, ShapeType type)
{
	assert(shp);
	assert(type >= NO_SHAPE && type <= T_SHAPE);

	int i;
	for(i = 0; i < 4; i++)
	{
		Point pt;
		pt.x = coordsTable[type][i][0];
		pt.y = coordsTable[type][i][1];
		shape_set_coordinate(shp, pt, i);
	}

	shp->type =  type;
}

void shape_set_random_type(Shape *shp)
{
	assert(shp);

	int t = rand() % 7 + 1;
	shape_set_type(shp, t);
}

void shape_set_coordinate(Shape *shp, Point pt, int index)
{
	assert(shp);
//	assert(pt);
	assert(index >= 0 && index <=3);
	shp->coords[index] = pt;
}

int shape_get_x_coordinate(Shape *shp, int index)
{
	return shp->coords[index].x;
}

int shape_get_y_coordinate(Shape *shp, int index)
{
	return shp->coords[index].y;
}

int shape_max_x(Shape *shp)
{
	int m = shp->coords[0].x;
	int i;
	for(i = 0; i < 4; i++)	
	{
		m = max(m, shp->coords[i].x);
	}
	return m;
}

int shape_max_y(Shape *shp)
{
	int m = shp->coords[0].y;
	int i;
	for(i = 0; i < 4; i++)
	{
		m = max(m, shp->coords[i].y);
	}
	return m;
}

int shape_min_x(Shape *shp)
{
	int m = shp->coords[0].x;
	int i;
	for(i = 0; i < 4; i++)
	{
		m = min(m, shp->coords[i].x);
	}
	return m;
}

int shape_min_y(Shape *shp)
{
	int m = shp->coords[0].y;
	int i;
	for(i = 0; i < 4; i++)
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
	shape_set_type(shape, type);
	
	return shape;
}

void shape_rotate_left(Shape *shp)
{
	if(shp->type == SQUARE_SHAPE)
		return;
	int i;
	for(i = 0; i < 4; i++)
	{
		int x = shp->coords[i].x;
		int y = shp->coords[i].y;
		shp->coords[i].x = -y;
		shp->coords[i].y = x;
	}
}

void shape_rotate_right(Shape *shp)
{
	if(shp->type == SQUARE_SHAPE)
		return;

	int i;	
	for(i = 0; i < 4; i++)
	{
		int x = shp->coords[i].x;
		int y = shp->coords[i].y;
		shp->coords[i].x = y;
		shp->coords[i].y = -x;
	}
}
