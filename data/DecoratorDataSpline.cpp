
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
	_b = (float *)malloc(sizeof(float) * data->size());
	_c = (float *)malloc(sizeof(float) * data->size());
	_d = (float *)malloc(sizeof(float) * data->size());

	//TODO make sure x axis is in increasing order

	refresh();
}

void DecoratorDataSpline::end(void) 
{
	free(_b);
	free(_c);
	free(_d);
}

Point DecoratorDataSpline::getPoint(int index)
{
	int bin = 0;
	Point p;

	if (index < _numElem)
	{
		p.x = (1.0 * index) / (_numElem-1);

		// check that we are in the correct bin
		while ((p.x > _data->getPoint(bin + 1).x))
		{
			bin++;
		}

		// compute interpolated y value
		p.y = _data->getPoint(bin).y +
			  _b[bin] * (p.x - _data->getPoint(bin).x) +
			  _c[bin] * (p.x - _data->getPoint(bin).x) * (p.x - _data->getPoint(bin).x) +
			  _d[bin] * (p.x - _data->getPoint(bin).x) * (p.x - _data->getPoint(bin).x) * (p.x - _data->getPoint(bin).x);

		// normalize data to a 0.0 .. 1.0 value
		p.y = (p.y - _yMin) / (_yMax - _yMin);

		//TODO this value needs to be interpolated between bin and bin+1
		p.value = _data->getPoint(bin).value; 
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

	// memset(_b, sizeof(float) * _data->size(), 0);
	// memset(_c, sizeof(float) * _data->size(), 0);
	// memset(_d, sizeof(float) * _data->size(), 0);

	if (_numElem >= _data->size())
	{
		int bin = 0;
		int n = (_data->size() - 1);
		float yInter;

		/** Step 0 */

		float h[n], A[n], l[n + 1], u[n + 1], z[n + 1];

		/** Step 1 */
		for (int i = 0; i <= n - 1; ++i)
		{
			h[i] = _data->getPoint(i + 1).x - _data->getPoint(i).x;
		}

		/** Step 2 */
		for (int i = 1; i <= n - 1; ++i)
		{
			/* we do not care if a has type int as it will always be divided by a float and become a float */
			A[i] = 3 * (_data->getPoint(i + 1).y - _data->getPoint(i).y) / h[i] - 3 * (_data->getPoint(i).y - _data->getPoint(i - 1).y) / h[i - 1];
		}

		/** Step 3 */
		l[0] = 1;
		u[0] = 0;
		z[0] = 0;

		/** Step 4 */
		for (int i = 1; i <= n - 1; ++i)
		{
			l[i] = 2 * (_data->getPoint(i + 1).x - _data->getPoint(i - 1).x) - h[i - 1] * u[i - 1];
			u[i] = h[i] / l[i];
			z[i] = (A[i] - h[i - 1] * z[i - 1]) / l[i];
		}

		/** Step 5 */
		l[n] = 1;
		z[n] = 0;
		_c[n] = 0;

		/** Step 6 */
		for (int j = n - 1; j >= 0; --j)
		{
			_c[j] = z[j] - u[j] * _c[j + 1];
			/* we do not care if a has type int as it will always be divided by a float and become a float */
			_b[j] = (_data->getPoint(j + 1).y - _data->getPoint(j).y) / h[j] - h[j] * (_c[j + 1] + 2 * _c[j]) / 3;
			_d[j] = (_c[j + 1] - _c[j]) / (3 * h[j]);
		}

		/* Interpolation done, check for new yMin yMax*/

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
					 _b[bin] * (px - _data->getPoint(bin).x) +
					 _c[bin] * (px - _data->getPoint(bin).x) * (px - _data->getPoint(bin).x) +
					 _d[bin] * (px - _data->getPoint(bin).x) * (px - _data->getPoint(bin).x) * (px - _data->getPoint(bin).x);

			/* Updated data min/max */
			if (yInter < _yMin)
				_yMin = yInter;
			if (yInter > _yMax)
				_yMax = yInter;
		}
	}
}
