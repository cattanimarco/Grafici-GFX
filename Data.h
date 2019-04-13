#ifndef ARDU_DATAVIS_DATA_H
#define ARDU_DATAVIS_DATA_H

#include "Geometry.h"

typedef Point *PointIterator;

class Data
{
public:
	void addPoint(Point point);
	void addPoints(Point *pointArray, int size);
	void addPoints(float *x, float *y, float *value, int size);
	PointIterator begin();
	PointIterator end();

private:
	LinkedList<Point> data;
	Point minPoint;
	Point maxPoint;
	Point avgPoint;
	int size = 0;
};

#endif //ARDU_DATAVIS_GEOMETRY_H
