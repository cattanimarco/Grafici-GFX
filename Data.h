#ifndef ARDU_DATAVIS_DATA_H
#define ARDU_DATAVIS_DATA_H

#include "Geometry.h"

class PointIterator;

class DataContainer
{
public:
	virtual Point getPoint(int index) = 0;
	virtual int size(void) = 0;
	virtual void refresh() = 0;
	PointIterator begin();
	PointIterator end();
};

class DataContainerFloat : public DataContainer
{
public:
	DataContainerFloat(float *xData, int len) : xData(xData), numElem(len) { refresh(); };
	DataContainerFloat(float *xData, float *yData, int len) : xData(xData), yData(yData), numElem(len) { refresh(); };
	Point getPoint(int index);
	void refresh();
	int size(void);

private:
	float *xData;
	float *yData;
	float xMin;
	float yMin;
	float xMax;
	float yMax;
	int numElem;
};

class PointIterator
{
	/* Inspired by https://www.boost.org/doc/libs/1_70_0/libs/iterator/doc/iterator_facade.html#tutorial-example */

public:
	PointIterator(DataContainer *dataContainer, int dataIndex) : dataContainer(dataContainer), dataIndex(dataIndex){};

	Point operator*();
	PointIterator &operator++();
	PointIterator operator++(int postfix);
	bool operator!=(PointIterator const &other);
	/*TODO complete operator overriding*/

private:
	DataContainer *dataContainer;
	int dataIndex;
};

// class Data
// {
// public:
// 	Data(DataContainer *dataContainer) : dataContainer(dataContainer){};
// 	PointIterator begin();
// 	PointIterator end();
// 	int len();

// private:
// 	DataContainer *dataContainer;
// };

#endif //ARDU_DATAVIS_DATA_H
