
#include "DecoratorDataSetHistogram.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#ifndef min
#define min(a, b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef max
#define max(a, b) (((a) > (b)) ? (a) : (b))
#endif

void DecoratorDataSetHistogram::begin(DataSet *dataset, int buckets)
{
	_dataset = dataset;
	_numElem = buckets;
	_counters = (int *)malloc(sizeof(int) * buckets);

	refresh();
}

void DecoratorDataSetHistogram::end(void)
{
	free(_counters);
}

DataPoint DecoratorDataSetHistogram::getDataPoint(int index)
{
	DataPoint p;
	if (index < _numElem)
	{
		p.x = (1.0 * index) / (_numElem - 1);
		p.y = (1.0 * _counters[index]) / _yMax;
	}

	return p;
}

int DecoratorDataSetHistogram::size(void)
{
	return _numElem;
}

void DecoratorDataSetHistogram::refresh(void)
{
	_yMax = 0;

	for (DataPointIterator it = _dataset->beginIt(); it != _dataset->endIt(); ++it)
	{
		DataPoint p = *it;
		int target = round(p.y * (_numElem - 1));
		_counters[target]++;
		_yMax = max(_counters[target], _yMax);
	}
}
