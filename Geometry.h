#ifndef ARDU_DATAVIS_GEOMETRY_H
#define ARDU_DATAVIS_GEOMETRY_H

#include <math.h>

struct Rectangle;

class Point
{
	public:
	float x;
	float y;
	float value;
	Point projectPoint(Rectangle rectangle);
};

//rename quadrilateral
struct Rectangle
{
	Point topLeft; // rename first
	Point topRight; // rename second (second needs to be linked to first and third)
	Point bottomLeft;
	Point bottomRight;
};

struct Boundaries
{
	Point topLeft; //change point to int
	Point bottomRight;
};

struct Line
{
	Point begin;
	Point end;
};

struct Circle
{
	Point center;
	float innerRadius;
	float outerRadius;
	float beginAngle;
	float endAngle;
};



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
