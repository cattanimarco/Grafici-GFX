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

float distance(Point a, Point b)
{
	sqrt(pow(a.x-b.x,2)+pow(a.y-b.y,2));
}

#endif //ARDU_DATAVIS_GEOMETRY_H
