#ifndef GRAFICI_DATA_H
#define GRAFICI_DATA_H

#include "Arduino.h"
#include "Macros.h"

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

class DataSet
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
	DataPointIterator(DataSet *dataSet, int dataIndex) : dataSet(dataSet), dataIndex(dataIndex){};

	DataPoint operator*();
	DataPointIterator &operator++();
	DataPointIterator operator++(int postfix);
	bool operator!=(DataPointIterator const &other);

private:
	DataSet *dataSet;
	int dataIndex;
};

#endif //GRAFICI_DATA_H
