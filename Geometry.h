#ifndef ARDU_DATAVIS_GEOMETRY_H
#define ARDU_DATAVIS_GEOMETRY_H

#include <math.h>

struct Point
{
	float x;
	float y;
	float value;
};

struct Line
{
	Point begin;
	Point end;
};

struct Rectangle
{
	Point topLeft;
	Point topRight;
	Point bottomLeft;
	Point bottomRight;
};

struct Circle
{
	Point center;
	float innerRadius;
	float outerRadius;
	float beginAngle;
	float endAngle;
};

Point projectPoint(Point normalizedPoint, Rectangle rectangle)
{
Point p;

p.x = (rectangle.bottomRight.x-rectangle.bottomLeft.x)*normalizedPoint.x + rectangle.bottomLeft.x;
p.y = (rectangle.topLeft.y-rectangle.bottomLeft.y)*normalizedPoint.y + rectangle.bottomLeft.y;

return p;
}

// float distance(Point a, Point b)
// {
// 	return sqrt(pow(a.x-b.x,2)+pow(a.y-b.y,2));
// }

// void swapPoint(Point &a, Point &b)
// {
// 	Point t = a;
// 	a = b;
// 	b = t;
// };

#endif //ARDU_DATAVIS_GEOMETRY_H
