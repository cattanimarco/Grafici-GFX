#ifndef ARDU_DATAVIS_DATA_H
#define ARDU_DATAVIS_DATA_H

#include "Geometry.h"

class PointIterator;

class Data
{
public:
	virtual Point getPoint(int index) = 0;
	virtual int size(void) = 0;
	virtual void refresh() = 0;
	PointIterator begin();
	PointIterator end();
};

class PointIterator
{

public:
	PointIterator(Data *data, int dataIndex) : _data(data), _dataIndex(dataIndex){};

	Point operator*();
	PointIterator &operator++();
	PointIterator operator++(int postfix);
	bool operator!=(PointIterator const &other);

private:
	Data *_data;
	int _dataIndex;
};

#endif //ARDU_DATAVIS_DATA_H
