#ifndef ARDU_DATAVIS_DATA_H
#define ARDU_DATAVIS_DATA_H

#include "Geometry.h"

typedef Point *PointIterator;

// class DataIterator
// {
// 	Data* parent;
// 	int index;
// 	/* override * and ++ */
// }




class Data
{
public:
	Point getPoint(int index);

	void loadData(float * dataArray, int size);
	void loadData(int * dataArray, int size);

	PointIterator begin();
	PointIterator end();

private:
	//LinkedList<Point> data;
	Point minPoint;
	Point maxPoint;
	Point avgPoint;
	int size;
};

class DataSimpleFloat : public Data
{
/* for unsigned floating point data in the range of 0.0 .. 1.0 */
};

class DataSimpleChar : public Data
{
/* for unsigned char data in the range of 0 .. 255 */
};

class DataSimpleInt : public Data
{
/* for unsigned int data in the range of 0 ..  */
};

class DataCustomFloat : public Data
{
/* for floating point data with custom range */
};

class DataCustomInt : public Data
{
/* for int data with custom range */
};

#endif //ARDU_DATAVIS_GEOMETRY_H
