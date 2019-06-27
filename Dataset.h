#ifndef ARDU_DATAVIS_DATA_H
#define ARDU_DATAVIS_DATA_H

#include "Geometry.h"

class PointIterator;

class Dataset
{
public:
	virtual Point getPoint(int index) = 0;
	virtual int size(void) = 0;
	virtual void refresh() = 0;
	 PointIterator beginIt();
	 PointIterator endIt();
};

class PointIterator
{

public:
	PointIterator(Dataset *dataset, int dataIndex) : _dataset(dataset), _dataIndex(dataIndex){};

	Point operator*();
	PointIterator &operator++();
	PointIterator operator++(int postfix);
	bool operator!=(PointIterator const &other);

private:
	Dataset *_dataset;
	int _dataIndex;
};

#endif //ARDU_DATAVIS_DATA_H
