
#include "DatasetHistogram.h"

#ifndef min
#define min(a, b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef max
#define max(a, b) (((a) > (b)) ? (a) : (b))
#endif

void DatasetHistogram::begin(Dataset *dataset, int buckets)
{
	_dataset = dataset;
	_numElem = buckets;
	_counters = (int *)malloc(sizeof(int) * buckets);

	refresh();
}

void DatasetHistogram::end(void)
{
	free(_counters);
}

Datapoint DatasetHistogram::getDatapoint(int index)
{
	Datapoint p;
	if (index < _numElem)
	{
		p.x = (1.0 * index) / (_numElem - 1);
		p.y = (1.0 * _counters[index]) / _yMax;
	}

	return p;
}

int DatasetHistogram::size(void)
{
	return _numElem;
}

void DatasetHistogram::refresh(void)
{
	_yMax = 0;

	for (DatapointIterator it = _dataset->beginIt(); it != _dataset->endIt(); ++it)
	{
		Datapoint p = *it;
		int target = round(p.y * (_numElem - 1));
		_counters[target]++;
		_yMax = max(_counters[target], _yMax);
	}
}
