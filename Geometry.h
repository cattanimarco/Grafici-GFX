#ifndef ARDUPLOT_GFX_GEOMETRY_H
#define ARDUPLOT_GFX_GEOMETRY_H


struct Point
{
	float value = 1.0;
	float x;
	float y;
};

struct Line
{
	Point start;
	Point stop;
};

struct Square
{
	Point topLeft;
	Point topRight;
	Point bottomLeft;
	Point bottomRight;
};

struct Circle
{
	Point centre;
	float innerRadius = 0.0;
	float outerRadius;
	float startAngle = 0.0;
	float stopAngle = 0.0;
};

#endif //ARDUPLOT_GFX_GEOMETRY_H
