
#include "DecoratorDataHistogram.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>

#ifndef min
#define min(a, b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef max
#define max(a, b) (((a) > (b)) ? (a) : (b))
#endif

void DecoratorDataHistogram::begin(Data *data, int buckets)
{
	_data = data;
	_numElem = buckets;
	_counters = (int *)malloc(sizeof(int) * buckets);

	refresh();
}

void DecoratorDataHistogram::end(void)
{
	free(_counters);
}

Point DecoratorDataHistogram::getPoint(int index)
{
	Point p;
	if (index < _numElem)
	{
		p.x = (1.0 * index) / (_numElem - 1);
		p.y = (1.0 * _counters[index]) / _yMax;
	}

	return p;
}

int DecoratorDataHistogram::size(void)
{
	return _numElem;
}

void DecoratorDataHistogram::refresh(void)
{
	_yMax = 0;

	for (PointIterator it = _data->begin(); it != _data->end(); ++it)
	{
		Point p = *it;
		int target = round(p.y * (_numElem - 1));
		_counters[target]++;
		_yMax = max(_counters[target], _yMax);
	}
}
