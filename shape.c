#include "shape.h"

shape* shape_new()
{
	shape* shp;
	shp = (shape*)malloc(sizeof(shape));
	return shp;
}

void shape_set_type(shape * shp, SHAPE_TYPE type)
{
	assert(shp);
	assert(type);
	assert(type >= NO_SHAPE && type <= T_SHAPE);
	shp->type =  type;
}

void shape_set_coordinate(shape *shp, point pt, int index)
{
	assert(shp);
	assert(pt);
	assert(index >= 0 && index <=3);
	shp->coordinates[index] = pt;
}


