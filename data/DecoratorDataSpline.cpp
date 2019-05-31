
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

DecoratorDataSpline::DecoratorDataSpline(Data *data, int interpolationSteps) : data(data), numElem(interpolationSteps)
{
	b = (float *)malloc(sizeof(float) * data->size());
	c = (float *)malloc(sizeof(float) * data->size());
	d = (float *)malloc(sizeof(float) * data->size());

	//TODO make sure x axis is in increasing order

	refresh();
}

Point DecoratorDataSpline::getPoint(int index)
{
	int bin = 0;
	Point p;

	if (index < numElem)
	{
		p.x = (1.0 * index) / numElem;

		// check that we are in the correct bin
		while ((p.x > data->getPoint(bin + 1).x))
		{
			bin++;
		}

		// compute interpolated y value
		p.y = data->getPoint(bin).y +
			  b[bin] * (p.x - data->getPoint(bin).x) +
			  c[bin] * (p.x - data->getPoint(bin).x) * (p.x - data->getPoint(bin).x) +
			  d[bin] * (p.x - data->getPoint(bin).x) * (p.x - data->getPoint(bin).x) * (p.x - data->getPoint(bin).x);

		// normalize data to a 0.0 .. 1.0 value
		p.y = (p.y - yMin) / (yMax - yMin);
	}

	return p;
}

int DecoratorDataSpline::size(void)
{
	return numElem;
}

void DecoratorDataSpline::refresh(void)
{
	// compute spline parameter, than scan all x values to find new min max
	yMax = 1;
	yMin = 0;

	memset(b, sizeof(float) * data->size(), 0);
	memset(c, sizeof(float) * data->size(), 0);
	memset(d, sizeof(float) * data->size(), 0);

	if (numElem >= data->size())
	{
		int bin = 0;
		int n = (data->size() - 1);
		float yInter;

		/** Step 0 */

		float h[n], A[n], l[n + 1], u[n + 1], z[n + 1];

		/** Step 1 */
		for (int i = 0; i <= n - 1; ++i)
		{
			h[i] = data->getPoint(i + 1).x - data->getPoint(i).x;
		}

		/** Step 2 */
		for (int i = 1; i <= n - 1; ++i)
		{
			/* we do not care if a has type int as it will always be divided by a float and become a float */
			A[i] = 3 * (data->getPoint(i + 1).y - data->getPoint(i).y) / h[i] - 3 * (data->getPoint(i).y - data->getPoint(i - 1).y) / h[i - 1];
		}

		/** Step 3 */
		l[0] = 1;
		u[0] = 0;
		z[0] = 0;

		/** Step 4 */
		for (int i = 1; i <= n - 1; ++i)
		{
			l[i] = 2 * (data->getPoint(i + 1).x - data->getPoint(i - 1).x) - h[i - 1] * u[i - 1];
			u[i] = h[i] / l[i];
			z[i] = (A[i] - h[i - 1] * z[i - 1]) / l[i];
		}

		/** Step 5 */
		l[n] = 1;
		z[n] = 0;
		c[n] = 0;

		/** Step 6 */
		for (int j = n - 1; j >= 0; --j)
		{
			c[j] = z[j] - u[j] * c[j + 1];
			/* we do not care if a has type int as it will always be divided by a float and become a float */
			b[j] = (data->getPoint(j + 1).y - data->getPoint(j).y) / h[j] - h[j] * (c[j + 1] + 2 * c[j]) / 3;
			d[j] = (c[j + 1] - c[j]) / (3 * h[j]);
		}

		/* Interpolation done, check for new yMin yMax*/

		bin = 0;
		for (float px = 0; px < 1; px += (1.0 / numElem))
		{

			/* check that we are in the correct bin */
			while ((px > data->getPoint(bin + 1).x))
			{
				bin++;
			}

			/* compute interpolated y value */

			yInter = data->getPoint(bin).y +
					 b[bin] * (px - data->getPoint(bin).x) +
					 c[bin] * (px - data->getPoint(bin).x) * (px - data->getPoint(bin).x) +
					 d[bin] * (px - data->getPoint(bin).x) * (px - data->getPoint(bin).x) * (px - data->getPoint(bin).x);

			/* Updated data min/max */
			if (yInter < yMin)
				yMin = yInter;
			if (yInter > yMax)
				yMax = yInter;
		}
	}
}
