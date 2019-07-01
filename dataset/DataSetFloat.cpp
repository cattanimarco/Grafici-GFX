#include "DataSetFloat.h"

#ifndef NULL
#define NULL (0)
#endif

#ifndef min
#define min(a, b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef max
#define max(a, b) (((a) > (b)) ? (a) : (b))
#endif

void DataSetFloat::begin(float *yDataPoint, float zValue, int len)
{
	_xDataPoint = NULL;
	_yDataPoint = yDataPoint;
	_zDataPoint = NULL;
	_zValue = zValue;
	_numElem = len;
	refresh();
};

void DataSetFloat::begin(float *yDataPoint, float *zDataPoint, int len)
{
	_xDataPoint = NULL;
	_yDataPoint = yDataPoint;
	_zDataPoint = zDataPoint;
	_zValue = 0;
	_numElem = len;
	refresh();
};

void DataSetFloat::begin(float *xDataPoint, float *yDataPoint, float zValue, int len)
{
	_xDataPoint = xDataPoint;
	_yDataPoint = yDataPoint;
	_zDataPoint = NULL;
	_zValue = zValue;
	_numElem = len;
	refresh();
};

void DataSetFloat::begin(float *xDataPoint, float *yDataPoint, float *zDataPoint, int len)
{
	_xDataPoint = xDataPoint;
	_yDataPoint = yDataPoint;
	_zDataPoint = zDataPoint;
	_zValue = 0;
	_numElem = len;
	refresh();
};

DataPoint DataSetFloat::getDataPoint(int index)
{
	DataPoint p;
	if (index < _numElem)
	{
		// normalize dataset to a 0.0 .. 1.0 value
		p.y = (_yDataPoint[index] - _yMin) / (_yMax - _yMin);

		if (_xDataPoint != NULL)
		{
			p.x = (_xDataPoint[index] - _xMin) / (_xMax - _xMin);
		}
		else
		{
			p.x = (1.0 * index) / (_numElem - 1);
		}

		//rewrite ho zdata is defined
		if (_zDataPoint != NULL)
		{
			p.value = (_zDataPoint[index] - _zMin) / (_zMax - _zMin);
		}
		else
		{
			p.value = _zValue;
		}
	}
	return p;
}

int DataSetFloat::size(void)
{
	return _numElem;
}

void DataSetFloat::refresh(void)
{
	if (_numElem > 0)
	{
		if (_yDataPoint != NULL)
		{
			_yMin = _yMax = _yDataPoint[0];
			for (int i = 1; i < _numElem; ++i)
			{
				_yMin = min(_yMin, _yDataPoint[i]);
				_yMax = max(_yMax, _yDataPoint[i]);
			}
		}

		if (_xDataPoint != NULL)
		{
			_xMin = _xMax = _xDataPoint[0];
			for (int i = 1; i < _numElem; ++i)
			{
				_xMin = min(_xMin, _xDataPoint[i]);
				_xMax = max(_xMax, _xDataPoint[i]);
			}
		}

		if (_zDataPoint != NULL)
		{
			_zMin = _zMax = _zDataPoint[0];
			for (int i = 1; i < _numElem; ++i)
			{
				_zMin = min(_zMin, _zDataPoint[i]);
				_zMax = max(_zMax, _zDataPoint[i]);
			}
		}
	}
}
