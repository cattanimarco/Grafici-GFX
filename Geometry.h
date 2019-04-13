#ifndef ARDU_DATAVIS_GEOMETRY_H
#define ARDU_DATAVIS_GEOMETRY_H


struct Point
{
	float value = 1.0;
	float x;
	float y;
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
	float innerRadius = 0.0;
	float outerRadius;
	float beginAngle = 0.0;
	float endAngle = 0.0;
};

#endif //ARDU_DATAVIS_GEOMETRY_H
