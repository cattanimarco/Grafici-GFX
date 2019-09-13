#ifndef GRAFICI_DATA_H
#define GRAFICI_DATA_H

#include "Arduino.h"

class DataPointIterator;

class DataPoint
{
public:
	DataPoint(void);
	DataPoint(float x, float y);
	DataPoint(float x, float y, float z);
	float x;
	float y;
	float z; // third dimension only visualized via color/size/etc..
};

class Dataset
{
public:
	virtual DataPoint getDataPoint(int index) = 0;
	virtual int size(void) = 0;
	virtual void refresh() = 0;
	 DataPointIterator beginIt();
	 DataPointIterator endIt();
};

class DataPointIterator
{

public:
	DataPointIterator(Dataset *dataset, int dataIndex) : _dataset(dataset), _dataIndex(dataIndex){};

	DataPoint operator*();
	DataPointIterator &operator++();
	DataPointIterator operator++(int postfix);
	bool operator!=(DataPointIterator const &other);

private:
	Dataset *_dataset;
	int _dataIndex;
};

#endif //GRAFICI_DATA_H
