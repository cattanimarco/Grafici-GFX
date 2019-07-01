#ifndef GRAFICI_DATA_H
#define GRAFICI_DATA_H


class DataPointIterator;

class DataPoint
{
public:
	DataPoint(void);
	DataPoint(float x, float y);
	float x;
	float y;
	float value;
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
	DataPointIterator(DataSet *dataset, int dataIndex) : _dataset(dataset), _dataIndex(dataIndex){};

	DataPoint operator*();
	DataPointIterator &operator++();
	DataPointIterator operator++(int postfix);
	bool operator!=(DataPointIterator const &other);

private:
	DataSet *_dataset;
	int _dataIndex;
};

#endif //GRAFICI_DATA_H
