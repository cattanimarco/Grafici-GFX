#include "Geometry.h"

Point Point::projectPoint(Rectangle rectangle)
{
	Point p;

	p.x = (rectangle.bottomRight.x - rectangle.bottomLeft.x) * x + rectangle.bottomLeft.x;
	p.y = (rectangle.topLeft.y - rectangle.bottomLeft.y) * y + rectangle.bottomLeft.y;

	return p;
};