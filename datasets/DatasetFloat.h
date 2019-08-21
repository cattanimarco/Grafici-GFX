#ifndef GRAFICI_GFX_DATA_FLOAT_H
#define GRAFICI_GFX_DATA_FLOAT_H

#include "../Data.h"

#define ZVALUE_FROM_X (-2.0)
#define ZVALUE_FROM_Y (2.0)

#ifndef NULL
#define NULL (0)
#endif

#ifndef min
#define min(a, b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef max
#define max(a, b) (((a) > (b)) ? (a) : (b))
#endif


class DatasetFloat : public Dataset
{
public:

	void begin(float *yDatapoint, float zValue, int len);
	void begin(float *yDatapoint, float *zDatapoint, int len);
	void begin(float *xDatapoint, float *yDatapoint, float zDatapoint, int len);
	void begin(float *xDatapoint, float *yDatapoint, float *zDatapoint, int len);
	
	Datapoint getDatapoint(int index);
	void refresh();
	int size(void);

private:
	float *_xDatapoint;
	float *_yDatapoint;
	float *_zDatapoint;
	float _zValue;

	float _xMin;
	float _yMin;
	float _zMin;
	
	float _xMax;
	float _yMax;
	float _zMax;
	
	int _numElem;
};

void DatasetFloat::begin(float *yDatapoint, float zValue, int len)
{
	_xDatapoint = NULL;
	_yDatapoint = yDatapoint;
	_zDatapoint = NULL;
	_zValue = zValue;
	_numElem = len;
	refresh();
};

void DatasetFloat::begin(float *yDatapoint, float *zDatapoint, int len)
{
	_xDatapoint = NULL;
	_yDatapoint = yDatapoint;
	_zDatapoint = zDatapoint;
	_zValue = 0;
	_numElem = len;
	refresh();
};

void DatasetFloat::begin(float *xDatapoint, float *yDatapoint, float zValue, int len)
{
	_xDatapoint = xDatapoint;
	_yDatapoint = yDatapoint;
	_zDatapoint = NULL;
	_zValue = zValue;
	_numElem = len;
	refresh();
};

void DatasetFloat::begin(float *xDatapoint, float *yDatapoint, float *zDatapoint, int len)
{
	_xDatapoint = xDatapoint;
	_yDatapoint = yDatapoint;
	_zDatapoint = zDatapoint;
	_zValue = 0;
	_numElem = len;
	refresh();
};

Datapoint DatasetFloat::getDatapoint(int index)
{
	Datapoint p;
	if (index < _numElem)
	{
		// normalize dataset to a 0.0 .. 1.0 value
		p.y = (_yDatapoint[index] - _yMin) / (_yMax - _yMin);

		if (_xDatapoint != NULL)
		{
			p.x = (_xDatapoint[index] - _xMin) / (_xMax - _xMin);
		}
		else
		{
			p.x = (1.0 * index) / (_numElem - 1);
		}

		//rewrite ho zdata is defined
		if (_zDatapoint != NULL)
		{
			p.value = (_zDatapoint[index] - _zMin) / (_zMax - _zMin);
		}
		else
		{
			p.value = _zValue;
		}
	}
	return p;
}

int DatasetFloat::size(void)
{
	return _numElem;
}

void DatasetFloat::refresh(void)
{
	if (_numElem > 0)
	{
		if (_yDatapoint != NULL)
		{
			_yMin = _yMax = _yDatapoint[0];
			for (int i = 1; i < _numElem; ++i)
			{
				_yMin = min(_yMin, _yDatapoint[i]);
				_yMax = max(_yMax, _yDatapoint[i]);
			}
		}

		if (_xDatapoint != NULL)
		{
			_xMin = _xMax = _xDatapoint[0];
			for (int i = 1; i < _numElem; ++i)
			{
				_xMin = min(_xMin, _xDatapoint[i]);
				_xMax = max(_xMax, _xDatapoint[i]);
			}
		}

		if (_zDatapoint != NULL)
		{
			_zMin = _zMax = _zDatapoint[0];
			for (int i = 1; i < _numElem; ++i)
			{
				_zMin = min(_zMin, _zDatapoint[i]);
				_zMax = max(_zMax, _zDatapoint[i]);
			}
		}
	}
}


#endif //GRAFICI_GFX_DATA_FLOAT_H
