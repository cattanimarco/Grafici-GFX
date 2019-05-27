#ifndef ARDU_DATAVIS_DATA_H
#define ARDU_DATAVIS_DATA_H

#include "Geometry.h"

class DataContainer
{
public:
	virtual Point getPoint(int index) = 0;
	virtual int size(void) = 0;
};

template <class T>
struct DataSourceDescriptor
{
	T *xData;
	T *yData;
	T xMin;
	T yMin;
	T xMax;
	T yMax;
	int size;
};

class DataContainerFloat : public DataContainer
{
public:
	DataContainerFloat(DataSourceDescriptor<float> dataSourceDescriptor) : dataSourceDescriptor(dataSourceDescriptor){};
	Point getPoint(int index);
	int size(void);

private:
	DataSourceDescriptor<float> dataSourceDescriptor;
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

class Data
{
public:
	Data(DataContainer *dataContainer) : dataContainer(dataContainer){};
	PointIterator begin();
	PointIterator end();
	int len();

private:
	DataContainer *dataContainer;
};

#endif //ARDU_DATAVIS_DATA_H
