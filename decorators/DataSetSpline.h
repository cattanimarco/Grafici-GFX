#ifndef GRAFICI_GFX_DATA_DECORATOR_SPLINE_H
#define GRAFICI_GFX_DATA_DECORATOR_SPLINE_H

#include "../Data.h"

class DataSetSpline : public DataSet
{
  public:
	DataSetSpline(){};
	~DataSetSpline();
	void begin(DataSet *dataSet, int interpolationSteps);
	DataPoint getDataPoint(int index);
	void refresh();
	int size(void);

  private:
	DataSet *dataSet;
	float xMin;
	float yMin;
	float valueMin;

	float xMax;
	float yMax;
	float valueMax;

	int numElem;

	//spline support arrays
	float *bY;
	float *cY;
	float *dY;

	float *bValue;
	float *cValue;
	float *dValue;
};

DataSetSpline::~DataSetSpline()
{
	// if (bY != nullptr)
	// 	free(bY);
	// if (cY != nullptr)
	// 	free(cY);
	// if (dY != nullptr)
	// 	free(dY);
	// if (bValue != nullptr)
	// 	free(bValue);
	// if (cValue != nullptr)
	// 	free(cValue);
	// if (dValue != nullptr)
	// 	free(dValue);
}

void DataSetSpline::begin(DataSet *dataSet, int interpolationSteps)
{
	this->dataSet = dataSet;
	numElem = interpolationSteps;
	bY = (float *)malloc(sizeof(float) * dataSet->size());
	cY = (float *)malloc(sizeof(float) * dataSet->size());
	dY = (float *)malloc(sizeof(float) * dataSet->size());
	bValue = (float *)malloc(sizeof(float) * dataSet->size());
	cValue = (float *)malloc(sizeof(float) * dataSet->size());
	dValue = (float *)malloc(sizeof(float) * dataSet->size());
	//TODO make sure x axis is in increasing order

	refresh();
}

DataPoint DataSetSpline::getDataPoint(int index)
{
	int bin = 0;
	DataPoint p;

	if (index < numElem)
	{
		p.x = (1.0 * index) / (numElem - 1);

		// check that we are in the correct bin
		while ((p.x > dataSet->getDataPoint(bin + 1).x))
		{
			bin++;
		}

		// compute interpolated y
		p.y = dataSet->getDataPoint(bin).y +
		      bY[bin] * (p.x - dataSet->getDataPoint(bin).x) +
		      cY[bin] * (p.x - dataSet->getDataPoint(bin).x) * (p.x - dataSet->getDataPoint(bin).x) +
		      dY[bin] * (p.x - dataSet->getDataPoint(bin).x) * (p.x - dataSet->getDataPoint(bin).x) * (p.x - dataSet->getDataPoint(bin).x);

		// normalize dataSet to a 0.0 .. 1.0 value
		p.y = (p.y - yMin) / (yMax - yMin);

		// compute interpolated value
		p.z = dataSet->getDataPoint(bin).z +
		      bValue[bin] * (p.x - dataSet->getDataPoint(bin).x) +
		      cValue[bin] * (p.x - dataSet->getDataPoint(bin).x) * (p.x - dataSet->getDataPoint(bin).x) +
		      dValue[bin] * (p.x - dataSet->getDataPoint(bin).x) * (p.x - dataSet->getDataPoint(bin).x) * (p.x - dataSet->getDataPoint(bin).x);

		// normalize dataSet to a 0.0 .. 1.0 value
		p.z = (p.z - valueMin) / (valueMax - valueMin);
	}

	return p;
}

int DataSetSpline::size(void)
{
	return numElem;
}

void DataSetSpline::refresh(void)
{
	dataSet->refresh();

	// compute spline parameter, than scan all x values to find new min max
	yMax = 1;
	yMin = 0;
	valueMax = 1;
	valueMin = 0;

	if (numElem >= dataSet->size())
	{
		int bin = 0;
		const int n = (dataSet->size() - 1);
		float yInter, valueInter;

		float *h = (float *)malloc(sizeof(float) * n);
		float *A = (float *)malloc(sizeof(float) * n);
		float *l = (float *)malloc(sizeof(float) * n + 1);
		float *u = (float *)malloc(sizeof(float) * n + 1);
		float *z = (float *)malloc(sizeof(float) * n + 1);

		for (int i = 0; i <= n - 1; ++i)
		{
			h[i] = dataSet->getDataPoint(i + 1).x - dataSet->getDataPoint(i).x;
		}

		// Interpolate Y axe
		for (int i = 1; i <= n - 1; ++i)
		{
			A[i] = 3 * (dataSet->getDataPoint(i + 1).y - dataSet->getDataPoint(i).y) / h[i] - 3 * (dataSet->getDataPoint(i).y - dataSet->getDataPoint(i - 1).y) / h[i - 1];
		}

		l[0] = 1;
		u[0] = 0;
		z[0] = 0;

		for (int i = 1; i <= n - 1; ++i)
		{
			l[i] = 2 * (dataSet->getDataPoint(i + 1).x - dataSet->getDataPoint(i - 1).x) - h[i - 1] * u[i - 1];
			u[i] = h[i] / l[i];
			z[i] = (A[i] - h[i - 1] * z[i - 1]) / l[i];
		}

		l[n] = 1;
		z[n] = 0;
		cY[n] = 0;

		for (int j = n - 1; j >= 0; --j)
		{
			cY[j] = z[j] - u[j] * cY[j + 1];
			bY[j] = (dataSet->getDataPoint(j + 1).y - dataSet->getDataPoint(j).y) / h[j] - h[j] * (cY[j + 1] + 2 * cY[j]) / 3;
			dY[j] = (cY[j + 1] - cY[j]) / (3 * h[j]);
		}

		// Interpolation done, check for new yMin yMax
		bin = 0;
		for (float px = 0; px < 1; px += (1.0 / numElem))
		{
			/* check that we are in the correct bin */
			while ((px > dataSet->getDataPoint(bin + 1).x))
			{
				bin++;
			}

			/* compute interpolated y value */
			yInter = dataSet->getDataPoint(bin).y +
			         bY[bin] * (px - dataSet->getDataPoint(bin).x) +
			         cY[bin] * (px - dataSet->getDataPoint(bin).x) * (px - dataSet->getDataPoint(bin).x) +
			         dY[bin] * (px - dataSet->getDataPoint(bin).x) * (px - dataSet->getDataPoint(bin).x) * (px - dataSet->getDataPoint(bin).x);

			/* Updated dataSet min/max */
			if (yInter < yMin)
				yMin = yInter;
			if (yInter > yMax)
				yMax = yInter;
		}

		// Interpolate value
		for (int i = 1; i <= n - 1; ++i)
		{
			A[i] = 3 * (dataSet->getDataPoint(i + 1).z - dataSet->getDataPoint(i).z) / h[i] - 3 * (dataSet->getDataPoint(i).z - dataSet->getDataPoint(i - 1).z) / h[i - 1];
		}

		l[0] = 1;
		u[0] = 0;
		z[0] = 0;

		for (int i = 1; i <= n - 1; ++i)
		{
			l[i] = 2 * (dataSet->getDataPoint(i + 1).x - dataSet->getDataPoint(i - 1).x) - h[i - 1] * u[i - 1];
			u[i] = h[i] / l[i];
			z[i] = (A[i] - h[i - 1] * z[i - 1]) / l[i];
		}

		l[n] = 1;
		z[n] = 0;
		cValue[n] = 0;

		for (int j = n - 1; j >= 0; --j)
		{
			cValue[j] = z[j] - u[j] * cValue[j + 1];
			bValue[j] = (dataSet->getDataPoint(j + 1).z - dataSet->getDataPoint(j).z) / h[j] - h[j] * (cValue[j + 1] + 2 * cValue[j]) / 3;
			dValue[j] = (cValue[j + 1] - cValue[j]) / (3 * h[j]);
		}

		// Interpolation done, check for new valueMin valueMax
		bin = 0;
		for (float px = 0; px < 1; px += (1.0 / numElem))
		{
			/* check that we are in the correct bin */
			while ((px > dataSet->getDataPoint(bin + 1).x))
			{
				bin++;
			}

			/* compute interpolated y value */
			valueInter = dataSet->getDataPoint(bin).z +
			             bValue[bin] * (px - dataSet->getDataPoint(bin).x) +
			             cValue[bin] * (px - dataSet->getDataPoint(bin).x) * (px - dataSet->getDataPoint(bin).x) +
			             dValue[bin] * (px - dataSet->getDataPoint(bin).x) * (px - dataSet->getDataPoint(bin).x) * (px - dataSet->getDataPoint(bin).x);

			/* Updated dataSet min/max */
			if (valueInter < valueMin)
				valueMin = valueInter;
			if (valueInter > valueMax)
				valueMax = valueInter;
		}
		free(h);
		free(A);
		free(l);
		free(u);
		free(z);
	}
}

#endif //GRAFICI_GFX_DATA_DECORATOR_SPLINE_H
