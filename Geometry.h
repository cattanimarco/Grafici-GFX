#ifndef ARDU_DATAVIS_GEOMETRY_H
#define ARDU_DATAVIS_GEOMETRY_H


struct Point
{
	float value;
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
	float innerRadius;
	float outerRadius;
	float beginAngle;
	float endAngle;
};

#endif //ARDU_DATAVIS_GEOMETRY_H
