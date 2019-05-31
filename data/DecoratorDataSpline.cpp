
#include "DataSpline.h"

#ifndef min
#define min(a, b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef max
#define max(a, b) (((a) > (b)) ? (a) : (b))
#endif

DataSpline::DataSpline(Data *data, int interpolationSteps) : numElem(interpolationSteps)
{
		yMax = 1.0;
		yMin = 0.0;
// compute new yMin-yMax
int bin = 0;
				int n = (dataX.size - 1);
				//T *a = dataY.data;
				float yInter;

				/** Step 0 */

				float h[n], A[n], l[n + 1], u[n + 1], z[n + 1], c[n + 1], b[n], d[n];

	for (PointIterator it = data->begin(); it != data->end(); ++it)
	{
		Point p = *it;
		h[i] = dataX.data[i + 1] - dataX.data[i];
	

				/** Step 1 */
				for (int i = 0; i <= n - 1; ++i)
				{
					h[i] = dataX.data[i + 1] - dataX.data[i];
				}

				/** Step 2 */
				for (int i = 1; i <= n - 1; ++i)
				{
					/* we do not care if a has type int as it will always be divided by a float and become a float */
					A[i] = 3 * (dataY.data[i + 1] - dataY.data[i]) / h[i] - 3 * (dataY.data[i] - dataY.data[i - 1]) / h[i - 1];
				}

				/** Step 3 */
				l[0] = 1;
				u[0] = 0;
				z[0] = 0;

				/** Step 4 */
				for (int i = 1; i <= n - 1; ++i)
				{
					l[i] = 2 * (dataX.data[i + 1] - dataX.data[i - 1]) - h[i - 1] * u[i - 1];
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
					b[j] = (dataY.data[j + 1] - dataY.data[j]) / h[j] - h[j] * (c[j + 1] + 2 * c[j]) / 3;
					d[j] = (c[j + 1] - c[j]) / (3 * h[j]);
				}

				/* Interpolation done */

				/* check for new yMin yMax*/
				bin = 0;
				for (float px = range.xMin; px < range.xMax; px += (range.xMax - range.xMin) / interpolationSteps)
				{
					/* check that we are in the correct bin */
					while ((px > dataX.data[bin + 1]))
						bin++;
					/* compute interpolated y value */

					yInter = dataY.data[bin] +
							 b[bin] * (px - dataX.data[bin]) +
							 c[bin] * (px - dataX.data[bin]) * (px - dataX.data[bin]) +
							 d[bin] * (px - dataX.data[bin]) * (px - dataX.data[bin]) * (px - dataX.data[bin]);

					/* Updated data min/max */
					if (yInter < yMinInter)
						yMinInter = yInter;
					if (yInter > yMaxInter)
						yMaxInter = yInter;
				}
			}
	}







}


Point DataFloat::getPoint(int index)
{
	Point p;
	if (index < numElem)
	{
		// normalize data to a 0.0 .. 1.0 value
		p.x = (xData[index] - xMin) / (xMax - xMin);
		if (yData != 0)
		{
			p.y = (yData[index] - yMin) / (yMax - yMin);
		}
		else
		{
			p.y = index / (numElem - 1.0);
		}
	}
	return p;
}

int DataFloat::size(void)
{
	return numElem;
}

void DataFloat::refresh(void)
{
	if (numElem > 0)
	{
		if (yData != 0)
		{
			yMin = yMax = yData[0];
			for (int i = 1; i < numElem; ++i)
			{
				yMin = min(yMin, yData[i]);
				yMax = max(yMax, yData[i]);
			}
		}

		if (xData != 0)
		{
			xMin = xMax = xData[0];
			for (int i = 1; i < numElem; ++i)
			{
				xMin = min(xMin, xData[i]);
				xMax = max(xMax, xData[i]);
			}
		}
	}
}



	

		/* do a spline per data array */

		/* compute new yMin and yMax */
		for (int yIdx = 0; yIdx < plotData.dataYs.size(); yIdx++)
		{
		}

		/* plot spline(s) */
		for (int yIdx = 0; yIdx < plotData.dataYs.size(); yIdx++)
		{
			DataArray_t<T> dataX = plotData.dataXs.get(yIdx);
			DataArray_t<T> dataY = plotData.dataYs.get(yIdx);

			if ((dataX.size > 1) && (interpolationSteps >= dataX.size))
			{
				int bin = 0;
				int previousX = -1;
				int previousY = -1;
				int n = (dataX.size - 1);
				T *a = dataY.data;
				float yInter;

				/** Step 0 */

				float h[n], A[n], l[n + 1], u[n + 1], z[n + 1], c[n + 1], b[n], d[n];

				/** Step 1 */
				for (int i = 0; i <= n - 1; ++i)
					h[i] = dataX.data[i + 1] - dataX.data[i];

				/** Step 2 */
				for (int i = 1; i <= n - 1; ++i)
					/* we do not care if a has type int as it will always be divided by a float and become a float */
					A[i] = 3 * (a[i + 1] - a[i]) / h[i] - 3 * (a[i] - a[i - 1]) / h[i - 1];

				/** Step 3 */
				l[0] = 1;
				u[0] = 0;
				z[0] = 0;

				/** Step 4 */
				for (int i = 1; i <= n - 1; ++i)
				{
					l[i] = 2 * (dataX.data[i + 1] - dataX.data[i - 1]) - h[i - 1] * u[i - 1];
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
					b[j] = (a[j + 1] - a[j]) / h[j] - h[j] * (c[j + 1] + 2 * c[j]) / 3;
					d[j] = (c[j + 1] - c[j]) / (3 * h[j]);
				}

				/* Interpolation done */

				/* plot spline */
				PlotColor_t lineC;
				cs->getHeatmapColor((1.0 + yIdx) / (plotData.dataYs.size() + 1), lineC);

				bin = 0;
				for (float px = range.xMin; px < range.xMax; px += (range.xMax - range.xMin) / interpolationSteps)
				{
					/* check that we are in the correct bin */
					while ((px > dataX.data[bin + 1]))
						bin++;

					/* compute interpolated y value */
					float interY = a[bin] +
								   b[bin] * (px - dataX.data[bin]) +
								   c[bin] * (px - dataX.data[bin]) * (px - dataX.data[bin]) +
								   d[bin] * (px - dataX.data[bin]) * (px - dataX.data[bin]) * (px - dataX.data[bin]);

					/* plot */
					int currentX = normalizeX(px, range.xMin, range.xMax);
					int currentY = normalizeY(interY, yMinInter, yMaxInter);
					if ((previousX > 0) && (previousY > 0))
					{
						tft->drawLine(previousX, previousY, currentX, currentY, ColorUtils::colorTo16b(lineC));
					}
					previousX = currentX;
					previousY = currentY;
				}

				/* plot the source data points (scatter, not interpolated) */
				for (int idx = 0; idx < dataX.size; idx++)
				{
					int currentX = normalizeX(dataX.data[idx], range.xMin, range.xMax);
					int currentY = normalizeY(dataY.data[idx], min(range.yMin, yMinInter), max(range.yMax, yMaxInter));
					tft->drawCircle(currentX, currentY, cs->pointSize, ColorUtils::colorTo16b(cs->lineColor));
				}
			}
		}