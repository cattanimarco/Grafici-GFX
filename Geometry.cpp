#include "Geometry.h"

Pixel Point::projectPoint(Boundaries boundaries)
{
	Pixel p;

	p.x = (boundaries.tr.x - boundaries.bl.x) * x + boundaries.bl.x;
	p.y = (boundaries.tr.y - boundaries.bl.y) * y + boundaries.bl.y;
	p.color = {255,255,255};

	return p;
};