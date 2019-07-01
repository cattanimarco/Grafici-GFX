
#include "DecoratorDataSetSpline.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>

#ifndef min
#define min(a, b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef max
#define max(a, b) (((a) > (b)) ? (a) : (b))
#endif


void DecoratorDataSetSpline::begin(DataSet *dataset, int interpolationSteps)
{
	_dataset = dataset;
	_numElem = interpolationSteps;
	_bY = (float *)malloc(sizeof(float) * dataset->size());
	_cY = (float *)malloc(sizeof(float) * dataset->size());
	_dY = (float *)malloc(sizeof(float) * dataset->size());
	_bValue = (float *)malloc(sizeof(float) * dataset->size());
	_cValue = (float *)malloc(sizeof(float) * dataset->size());
	_dValue = (float *)malloc(sizeof(float) * dataset->size());
	//TODO make sure x axis is in increasing order

	refresh();
}

void DecoratorDataSetSpline::end(void)
{
	free(_bY);
	free(_cY);
	free(_dY);
	free(_bValue);
	free(_cValue);
	free(_dValue);
}

DataPoint DecoratorDataSetSpline::getDataPoint(int index)
{
	int bin = 0;
	DataPoint p;

	if (index < _numElem)
	{
		p.x = (1.0 * index) / (_numElem - 1);

		// check that we are in the correct bin
		while ((p.x > _dataset->getDataPoint(bin + 1).x))
		{
			bin++;
		}

		// compute interpolated y
		p.y = _dataset->getDataPoint(bin).y +
			  _bY[bin] * (p.x - _dataset->getDataPoint(bin).x) +
			  _cY[bin] * (p.x - _dataset->getDataPoint(bin).x) * (p.x - _dataset->getDataPoint(bin).x) +
			  _dY[bin] * (p.x - _dataset->getDataPoint(bin).x) * (p.x - _dataset->getDataPoint(bin).x) * (p.x - _dataset->getDataPoint(bin).x);

		// normalize dataset to a 0.0 .. 1.0 value
		p.y = (p.y - _yMin) / (_yMax - _yMin);

		// compute interpolated value
		p.value = _dataset->getDataPoint(bin).value +
			  _bValue[bin] * (p.x - _dataset->getDataPoint(bin).x) +
			  _cValue[bin] * (p.x - _dataset->getDataPoint(bin).x) * (p.x - _dataset->getDataPoint(bin).x) +
			  _dValue[bin] * (p.x - _dataset->getDataPoint(bin).x) * (p.x - _dataset->getDataPoint(bin).x) * (p.x - _dataset->getDataPoint(bin).x);

		// normalize dataset to a 0.0 .. 1.0 value
		p.value = (p.value - _valueMin) / (_valueMax - _valueMin);
	}

	return p;
}

int DecoratorDataSetSpline::size(void)
{
	return _numElem;
}

void DecoratorDataSetSpline::refresh(void)
{
	_dataset->refresh();
	
	// compute spline parameter, than scan all x values to find new min max
	_yMax = 1;
	_yMin = 0;
	_valueMax = 1;
	_valueMin = 0;

	// memset(_bY, sizeof(float) * _dataset->size(), 0);
	// memset(_cY, sizeof(float) * _dataset->size(), 0);
	// memset(_dY, sizeof(float) * _dataset->size(), 0);

	if (_numElem >= _dataset->size())
	{
		int bin = 0;
		int n = (_dataset->size() - 1);
		float yInter, valueInter;
		float h[n], A[n], l[n + 1], u[n + 1], z[n + 1];

		for (int i = 0; i <= n - 1; ++i)
		{
			h[i] = _dataset->getDataPoint(i + 1).x - _dataset->getDataPoint(i).x;
		}

		// Interpolate Y axe
		for (int i = 1; i <= n - 1; ++i)
		{
			A[i] = 3 * (_dataset->getDataPoint(i + 1).y - _dataset->getDataPoint(i).y) / h[i] - 3 * (_dataset->getDataPoint(i).y - _dataset->getDataPoint(i - 1).y) / h[i - 1];
		}

		l[0] = 1;
		u[0] = 0;
		z[0] = 0;

		for (int i = 1; i <= n - 1; ++i)
		{
			l[i] = 2 * (_dataset->getDataPoint(i + 1).x - _dataset->getDataPoint(i - 1).x) - h[i - 1] * u[i - 1];
			u[i] = h[i] / l[i];
			z[i] = (A[i] - h[i - 1] * z[i - 1]) / l[i];
		}

		l[n] = 1;
		z[n] = 0;
		_cY[n] = 0;

		for (int j = n - 1; j >= 0; --j)
		{
			_cY[j] = z[j] - u[j] * _cY[j + 1];
			_bY[j] = (_dataset->getDataPoint(j + 1).y - _dataset->getDataPoint(j).y) / h[j] - h[j] * (_cY[j + 1] + 2 * _cY[j]) / 3;
			_dY[j] = (_cY[j + 1] - _cY[j]) / (3 * h[j]);
		}

		// Interpolation done, check for new yMin yMax
		bin = 0;
		for (float px = 0; px < 1; px += (1.0 / _numElem))
		{
			/* check that we are in the correct bin */
			while ((px > _dataset->getDataPoint(bin + 1).x))
			{
				bin++;
			}
			
			/* compute interpolated y value */
			yInter = _dataset->getDataPoint(bin).y +
					 _bY[bin] * (px - _dataset->getDataPoint(bin).x) +
					 _cY[bin] * (px - _dataset->getDataPoint(bin).x) * (px - _dataset->getDataPoint(bin).x) +
					 _dY[bin] * (px - _dataset->getDataPoint(bin).x) * (px - _dataset->getDataPoint(bin).x) * (px - _dataset->getDataPoint(bin).x);

			/* Updated dataset min/max */
			if (yInter < _yMin)
				_yMin = yInter;
			if (yInter > _yMax)
				_yMax = yInter;
		}

		// Interpolate value
		for (int i = 1; i <= n - 1; ++i)
		{
			A[i] = 3 * (_dataset->getDataPoint(i + 1).value - _dataset->getDataPoint(i).value) / h[i] - 3 * (_dataset->getDataPoint(i).value - _dataset->getDataPoint(i - 1).value) / h[i - 1];
		}

		l[0] = 1;
		u[0] = 0;
		z[0] = 0;

		for (int i = 1; i <= n - 1; ++i)
		{
			l[i] = 2 * (_dataset->getDataPoint(i + 1).x - _dataset->getDataPoint(i - 1).x) - h[i - 1] * u[i - 1];
			u[i] = h[i] / l[i];
			z[i] = (A[i] - h[i - 1] * z[i - 1]) / l[i];
		}

		l[n] = 1;
		z[n] = 0;
		_cValue[n] = 0;

		for (int j = n - 1; j >= 0; --j)
		{
			_cValue[j] = z[j] - u[j] * _cValue[j + 1];
			_bValue[j] = (_dataset->getDataPoint(j + 1).value - _dataset->getDataPoint(j).value) / h[j] - h[j] * (_cValue[j + 1] + 2 * _cValue[j]) / 3;
			_dValue[j] = (_cValue[j + 1] - _cValue[j]) / (3 * h[j]);
		}

		// Interpolation done, check for new valueMin valueMax
		bin = 0;
		for (float px = 0; px < 1; px += (1.0 / _numElem))
		{
			/* check that we are in the correct bin */
			while ((px > _dataset->getDataPoint(bin + 1).x))
			{
				bin++;
			}
			
			/* compute interpolated y value */
			valueInter = _dataset->getDataPoint(bin).value +
					 _bValue[bin] * (px - _dataset->getDataPoint(bin).x) +
					 _cValue[bin] * (px - _dataset->getDataPoint(bin).x) * (px - _dataset->getDataPoint(bin).x) +
					 _dValue[bin] * (px - _dataset->getDataPoint(bin).x) * (px - _dataset->getDataPoint(bin).x) * (px - _dataset->getDataPoint(bin).x);

			/* Updated dataset min/max */
			if (valueInter < _valueMin)
				_valueMin = valueInter;
			if (valueInter > _valueMax)
				_valueMax = valueInter;
		}


	}
}
