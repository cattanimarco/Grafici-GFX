
#include "DecoratorDataSpline.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>

#ifndef min
#define min(a, b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef max
#define max(a, b) (((a) > (b)) ? (a) : (b))
#endif


void DecoratorDataSpline::begin(Data *data, int interpolationSteps)
{
	_data = data;
	_numElem = interpolationSteps;
	_bY = (float *)malloc(sizeof(float) * data->size());
	_cY = (float *)malloc(sizeof(float) * data->size());
	_dY = (float *)malloc(sizeof(float) * data->size());
	_bValue = (float *)malloc(sizeof(float) * data->size());
	_cValue = (float *)malloc(sizeof(float) * data->size());
	_dValue = (float *)malloc(sizeof(float) * data->size());
	//TODO make sure x axis is in increasing order

	refresh();
}

void DecoratorDataSpline::end(void)
{
	free(_bY);
	free(_cY);
	free(_dY);
	free(_bValue);
	free(_cValue);
	free(_dValue);
}

Point DecoratorDataSpline::getPoint(int index)
{
	int bin = 0;
	Point p;

	if (index < _numElem)
	{
		p.x = (1.0 * index) / (_numElem - 1);

		// check that we are in the correct bin
		while ((p.x > _data->getPoint(bin + 1).x))
		{
			bin++;
		}

		// compute interpolated y
		p.y = _data->getPoint(bin).y +
			  _bY[bin] * (p.x - _data->getPoint(bin).x) +
			  _cY[bin] * (p.x - _data->getPoint(bin).x) * (p.x - _data->getPoint(bin).x) +
			  _dY[bin] * (p.x - _data->getPoint(bin).x) * (p.x - _data->getPoint(bin).x) * (p.x - _data->getPoint(bin).x);

		// normalize data to a 0.0 .. 1.0 value
		p.y = (p.y - _yMin) / (_yMax - _yMin);

		// compute interpolated value
		p.value = _data->getPoint(bin).value +
			  _bValue[bin] * (p.x - _data->getPoint(bin).x) +
			  _cValue[bin] * (p.x - _data->getPoint(bin).x) * (p.x - _data->getPoint(bin).x) +
			  _dValue[bin] * (p.x - _data->getPoint(bin).x) * (p.x - _data->getPoint(bin).x) * (p.x - _data->getPoint(bin).x);

		// normalize data to a 0.0 .. 1.0 value
		p.value = (p.value - _valueMin) / (_valueMax - _valueMin);
	}

	return p;
}

int DecoratorDataSpline::size(void)
{
	return _numElem;
}

void DecoratorDataSpline::refresh(void)
{
	// compute spline parameter, than scan all x values to find new min max
	_yMax = 1;
	_yMin = 0;
	_valueMax = 1;
	_valueMin = 0;

	// memset(_bY, sizeof(float) * _data->size(), 0);
	// memset(_cY, sizeof(float) * _data->size(), 0);
	// memset(_dY, sizeof(float) * _data->size(), 0);

	if (_numElem >= _data->size())
	{
		int bin = 0;
		int n = (_data->size() - 1);
		float yInter, valueInter;
		float h[n], A[n], l[n + 1], u[n + 1], z[n + 1];

		for (int i = 0; i <= n - 1; ++i)
		{
			h[i] = _data->getPoint(i + 1).x - _data->getPoint(i).x;
		}

		// Interpolate Y axe
		for (int i = 1; i <= n - 1; ++i)
		{
			A[i] = 3 * (_data->getPoint(i + 1).y - _data->getPoint(i).y) / h[i] - 3 * (_data->getPoint(i).y - _data->getPoint(i - 1).y) / h[i - 1];
		}

		l[0] = 1;
		u[0] = 0;
		z[0] = 0;

		for (int i = 1; i <= n - 1; ++i)
		{
			l[i] = 2 * (_data->getPoint(i + 1).x - _data->getPoint(i - 1).x) - h[i - 1] * u[i - 1];
			u[i] = h[i] / l[i];
			z[i] = (A[i] - h[i - 1] * z[i - 1]) / l[i];
		}

		l[n] = 1;
		z[n] = 0;
		_cY[n] = 0;

		for (int j = n - 1; j >= 0; --j)
		{
			_cY[j] = z[j] - u[j] * _cY[j + 1];
			_bY[j] = (_data->getPoint(j + 1).y - _data->getPoint(j).y) / h[j] - h[j] * (_cY[j + 1] + 2 * _cY[j]) / 3;
			_dY[j] = (_cY[j + 1] - _cY[j]) / (3 * h[j]);
		}

		// Interpolation done, check for new yMin yMax
		bin = 0;
		for (float px = 0; px < 1; px += (1.0 / _numElem))
		{
			/* check that we are in the correct bin */
			while ((px > _data->getPoint(bin + 1).x))
			{
				bin++;
			}
			
			/* compute interpolated y value */
			yInter = _data->getPoint(bin).y +
					 _bY[bin] * (px - _data->getPoint(bin).x) +
					 _cY[bin] * (px - _data->getPoint(bin).x) * (px - _data->getPoint(bin).x) +
					 _dY[bin] * (px - _data->getPoint(bin).x) * (px - _data->getPoint(bin).x) * (px - _data->getPoint(bin).x);

			/* Updated data min/max */
			if (yInter < _yMin)
				_yMin = yInter;
			if (yInter > _yMax)
				_yMax = yInter;
		}

		// Interpolate value
		for (int i = 1; i <= n - 1; ++i)
		{
			A[i] = 3 * (_data->getPoint(i + 1).value - _data->getPoint(i).value) / h[i] - 3 * (_data->getPoint(i).value - _data->getPoint(i - 1).value) / h[i - 1];
		}

		l[0] = 1;
		u[0] = 0;
		z[0] = 0;

		for (int i = 1; i <= n - 1; ++i)
		{
			l[i] = 2 * (_data->getPoint(i + 1).x - _data->getPoint(i - 1).x) - h[i - 1] * u[i - 1];
			u[i] = h[i] / l[i];
			z[i] = (A[i] - h[i - 1] * z[i - 1]) / l[i];
		}

		l[n] = 1;
		z[n] = 0;
		_cValue[n] = 0;

		for (int j = n - 1; j >= 0; --j)
		{
			_cValue[j] = z[j] - u[j] * _cValue[j + 1];
			_bValue[j] = (_data->getPoint(j + 1).value - _data->getPoint(j).value) / h[j] - h[j] * (_cValue[j + 1] + 2 * _cValue[j]) / 3;
			_dValue[j] = (_cValue[j + 1] - _cValue[j]) / (3 * h[j]);
		}

		// Interpolation done, check for new valueMin valueMax
		bin = 0;
		for (float px = 0; px < 1; px += (1.0 / _numElem))
		{
			/* check that we are in the correct bin */
			while ((px > _data->getPoint(bin + 1).x))
			{
				bin++;
			}
			
			/* compute interpolated y value */
			valueInter = _data->getPoint(bin).value +
					 _bValue[bin] * (px - _data->getPoint(bin).x) +
					 _cValue[bin] * (px - _data->getPoint(bin).x) * (px - _data->getPoint(bin).x) +
					 _dValue[bin] * (px - _data->getPoint(bin).x) * (px - _data->getPoint(bin).x) * (px - _data->getPoint(bin).x);

			/* Updated data min/max */
			if (valueInter < _valueMin)
				_valueMin = valueInter;
			if (valueInter > _valueMax)
				_valueMax = valueInter;
		}


	}
}
