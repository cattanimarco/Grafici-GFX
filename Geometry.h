#ifndef ARDU_DATAVIS_GEOMETRY_H
#define ARDU_DATAVIS_GEOMETRY_H

#include <math.h>

#include "Colors.h"

struct Pixel
{
public:
	Pixel(void);
	Pixel(float x, float y);
	Pixel(float x, float y, Color color);

	Pixel &setColor(Color color);
	Pixel &setColor(float value, Gradient gradient);

	Pixel &darkerColor(float percentage);

	Pixel &operator+=(const Pixel &b);
	Pixel &operator-=(const Pixel &b);

	float x;
	float y;
	Color color;
};

struct Line
{
	Pixel begin;
	Pixel end;
};

struct Boundaries
{
	Pixel bl;
	Pixel tr;
};

class Point
{
public:
	Point(void);
	Point(float x, float y);
	float x;
	float y;
	float value;
	Pixel projectPoint(Boundaries boundaries);
	//	Pixel projectPoint(Boundaries boundaries,style);
};

// add class for poligon: list of point
// to draw 6 point polygon: draw 123 134 145 156

//rename quadrilateral
struct Rectangle
{
	Pixel topLeft;  // rename first
	Pixel topRight; // rename second (second needs to be linked to first and third)
	Pixel bottomLeft;
	Pixel bottomRight;
};

struct Circle
{
	Pixel center;
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
