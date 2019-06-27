#include "DataFloat.h"

#ifndef NULL
#define NULL (0)
#endif

#ifndef min
#define min(a, b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef max
#define max(a, b) (((a) > (b)) ? (a) : (b))
#endif

void DataFloat::begin(float *yData, float zValue, int len)
{
	_xData = NULL;
	_yData = yData;
	_zData = NULL;
	_zValue = zValue;
	_numElem = len;
	refresh();
};

void DataFloat::begin(float *yData, float *zData, int len)
{
	_xData = NULL;
	_yData = yData;
	_zData = zData;
	_zValue = 0;
	_numElem = len;
	refresh();
};

void DataFloat::begin(float *xData, float *yData, float zValue, int len)
{
	_xData = xData;
	_yData = yData;
	_zData = NULL;
	_zValue = zValue;
	_numElem = len;
	refresh();
};

void DataFloat::begin(float *xData, float *yData, float *zData, int len)
{
	_xData = xData;
	_yData = yData;
	_zData = zData;
	_zValue = 0;
	_numElem = len;
	refresh();
};

Point DataFloat::getPoint(int index)
{
	Point p;
	if (index < _numElem)
	{
		// normalize dataset to a 0.0 .. 1.0 value
		p.y = (_yData[index] - _yMin) / (_yMax - _yMin);

		if (_xData != NULL)
		{
			p.x = (_xData[index] - _xMin) / (_xMax - _xMin);
		}
		else
		{
			p.x = (1.0 * index) / (_numElem - 1);
		}

		//rewrite ho zdata is defined
		if (_zData != NULL)
		{
			p.value = (_zData[index] - _zMin) / (_zMax - _zMin);
		}
		else
		{
			p.value = _zValue;
		}
	}
	return p;
}

int DataFloat::size(void)
{
	return _numElem;
}

void DataFloat::refresh(void)
{
	if (_numElem > 0)
	{
		if (_yData != NULL)
		{
			_yMin = _yMax = _yData[0];
			for (int i = 1; i < _numElem; ++i)
			{
				_yMin = min(_yMin, _yData[i]);
				_yMax = max(_yMax, _yData[i]);
			}
		}

		if (_xData != NULL)
		{
			_xMin = _xMax = _xData[0];
			for (int i = 1; i < _numElem; ++i)
			{
				_xMin = min(_xMin, _xData[i]);
				_xMax = max(_xMax, _xData[i]);
			}
		}

		if (_zData != NULL)
		{
			_zMin = _zMax = _zData[0];
			for (int i = 1; i < _numElem; ++i)
			{
				_zMin = min(_zMin, _zData[i]);
				_zMax = max(_zMax, _zData[i]);
			}
		}
	}
}
