#ifndef ARDUPLOT_GFX_DATA_H
#define ARDUPLOT_GFX_DATA_H

typedef *Point DataIterator;

class Data
{
  public:
	Data();
	addPoint(Point point);
	DataIterator begin();
	DataIterator end();

  private:
	LinkedList<Point> data;
	Point min; // store min x, y, value
	Point max; // store max x, y, value
};

#endif //ARDUPLOT_GFX_GEOMETRY_H
