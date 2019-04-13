#ifndef ARDUPLOT_GFX_DATA_H
#define ARDUPLOT_GFX_DATA_H

typedef *Point PointIterator;

class Data
{
  public:
	addPoint(Point point);
	addPoints(Point *pointArray, int size);
	addPoints(float * x, float * y, float * value, int size);
	PointIterator begin();
	PointIterator end();

  private:
	LinkedList<Point> data;
	Point minPoint;
	Point maxPoint;
	Point avgPoint;
	int size = 0;
};

#endif //ARDUPLOT_GFX_GEOMETRY_H
