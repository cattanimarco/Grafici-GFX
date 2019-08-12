#ifndef GRAFICI_DATA_H
#define GRAFICI_DATA_H

#include "Arduino.h"

class DatapointIterator;

class Datapoint
{
public:
	Datapoint(void);
	Datapoint(float x, float y);
	float x;
	float y;
	float value;
};

class Dataset
{
public:
	virtual Datapoint getDatapoint(int index) = 0;
	virtual int size(void) = 0;
	virtual void refresh() = 0;
	 DatapointIterator beginIt();
	 DatapointIterator endIt();
};

class DatapointIterator
{

public:
	DatapointIterator(Dataset *dataset, int dataIndex) : _dataset(dataset), _dataIndex(dataIndex){};

	Datapoint operator*();
	DatapointIterator &operator++();
	DatapointIterator operator++(int postfix);
	bool operator!=(DatapointIterator const &other);

private:
	Dataset *_dataset;
	int _dataIndex;
};

#endif //GRAFICI_DATA_H
