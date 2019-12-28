#ifndef GRAFICI_GFX_DATA_DECORATOR_SPLINE_H
#define GRAFICI_GFX_DATA_DECORATOR_SPLINE_H

#include "../Data.h"

class DataSetSpline : public DataSet
{
  public:
	DataSetSpline(){};
	~DataSetSpline();
	void begin(DataSet &dataSet, int interpolationSteps);
	DataCoordinates getDataCoordinate(int index);
	void refresh();
	int size(void);

  private:
	DataSet *dataSet;
	float yMin;
	float zMin;

	float yMax;
	float zMax;

	int numElem;

	//spline support arrays
	float *bY;
	float *cY;
	float *dY;

	float *bZ;
	float *cZ;
	float *dZ;
};

DataSetSpline::~DataSetSpline()
{
	// if (bY != nullptr)
	// 	free(bY);
	// if (cY != nullptr)
	// 	free(cY);
	// if (dY != nullptr)
	// 	free(dY);
	// if (bZ != nullptr)
	// 	free(bZ);
	// if (cZ != nullptr)
	// 	free(cZ);
	// if (dZ != nullptr)
	// 	free(dZ);
}

void DataSetSpline::begin(DataSet &dataSet, int interpolationSteps)
{
	this->dataSet = &dataSet;
	numElem = interpolationSteps;
	bY = (float *)malloc(sizeof(float) * dataSet.size());
	cY = (float *)malloc(sizeof(float) * dataSet.size());
	dY = (float *)malloc(sizeof(float) * dataSet.size());
	bZ = (float *)malloc(sizeof(float) * dataSet.size());
	cZ = (float *)malloc(sizeof(float) * dataSet.size());
	dZ = (float *)malloc(sizeof(float) * dataSet.size());
	//TODO make sure x axis is in increasing order

	refresh();
}

DataCoordinates DataSetSpline::getDataCoordinate(int index)
{
	int bin = 0;
	DataCoordinates p;

	if (index < numElem)
	{
		p.x = (1.0 * index) / (numElem - 1);

		// check that we are in the correct bin
		while ((p.x > dataSet->getDataCoordinate(bin + 1).x))
		{
			bin++;
		}

		// compute interpolated y
		p.y = dataSet->getDataCoordinate(bin).y +
		      bY[bin] * (p.x - dataSet->getDataCoordinate(bin).x) +
		      cY[bin] * (p.x - dataSet->getDataCoordinate(bin).x) * (p.x - dataSet->getDataCoordinate(bin).x) +
		      dY[bin] * (p.x - dataSet->getDataCoordinate(bin).x) * (p.x - dataSet->getDataCoordinate(bin).x) * (p.x - dataSet->getDataCoordinate(bin).x);

		// normalize dataSet to a 0.0 .. 1.0 value
		p.y = (p.y - yMin) / (yMax - yMin);

		// compute interpolated value
		p.z = dataSet->getDataCoordinate(bin).z +
		      bZ[bin] * (p.x - dataSet->getDataCoordinate(bin).x) +
		      cZ[bin] * (p.x - dataSet->getDataCoordinate(bin).x) * (p.x - dataSet->getDataCoordinate(bin).x) +
		      dZ[bin] * (p.x - dataSet->getDataCoordinate(bin).x) * (p.x - dataSet->getDataCoordinate(bin).x) * (p.x - dataSet->getDataCoordinate(bin).x);

		// normalize dataSet to a 0.0 .. 1.0 value
		p.z = (p.z - zMin) / (zMax - zMin);
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
	zMax = 1;
	zMin = 0;

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
			h[i] = dataSet->getDataCoordinate(i + 1).x - dataSet->getDataCoordinate(i).x;
		}

		// Interpolate Y axe
		for (int i = 1; i <= n - 1; ++i)
		{
			A[i] = 3 * (dataSet->getDataCoordinate(i + 1).y - dataSet->getDataCoordinate(i).y) / h[i] - 3 * (dataSet->getDataCoordinate(i).y - dataSet->getDataCoordinate(i - 1).y) / h[i - 1];
		}

		l[0] = 1;
		u[0] = 0;
		z[0] = 0;

		for (int i = 1; i <= n - 1; ++i)
		{
			l[i] = 2 * (dataSet->getDataCoordinate(i + 1).x - dataSet->getDataCoordinate(i - 1).x) - h[i - 1] * u[i - 1];
			u[i] = h[i] / l[i];
			z[i] = (A[i] - h[i - 1] * z[i - 1]) / l[i];
		}

		l[n] = 1;
		z[n] = 0;
		cY[n] = 0;

		for (int j = n - 1; j >= 0; --j)
		{
			cY[j] = z[j] - u[j] * cY[j + 1];
			bY[j] = (dataSet->getDataCoordinate(j + 1).y - dataSet->getDataCoordinate(j).y) / h[j] - h[j] * (cY[j + 1] + 2 * cY[j]) / 3;
			dY[j] = (cY[j + 1] - cY[j]) / (3 * h[j]);
		}

		// Interpolation done, check for new yMin yMax
		bin = 0;
		for (float px = 0; px < 1; px += (1.0 / numElem))
		{
			/* check that we are in the correct bin */
			while ((px > dataSet->getDataCoordinate(bin + 1).x))
			{
				bin++;
			}

			/* compute interpolated y value */
			yInter = dataSet->getDataCoordinate(bin).y +
			         bY[bin] * (px - dataSet->getDataCoordinate(bin).x) +
			         cY[bin] * (px - dataSet->getDataCoordinate(bin).x) * (px - dataSet->getDataCoordinate(bin).x) +
			         dY[bin] * (px - dataSet->getDataCoordinate(bin).x) * (px - dataSet->getDataCoordinate(bin).x) * (px - dataSet->getDataCoordinate(bin).x);

			/* Updated dataSet min/max */
			if (yInter < yMin)
				yMin = yInter;
			if (yInter > yMax)
				yMax = yInter;
		}

		// Interpolate value
		for (int i = 1; i <= n - 1; ++i)
		{
			A[i] = 3 * (dataSet->getDataCoordinate(i + 1).z - dataSet->getDataCoordinate(i).z) / h[i] - 3 * (dataSet->getDataCoordinate(i).z - dataSet->getDataCoordinate(i - 1).z) / h[i - 1];
		}

		l[0] = 1;
		u[0] = 0;
		z[0] = 0;

		for (int i = 1; i <= n - 1; ++i)
		{
			l[i] = 2 * (dataSet->getDataCoordinate(i + 1).x - dataSet->getDataCoordinate(i - 1).x) - h[i - 1] * u[i - 1];
			u[i] = h[i] / l[i];
			z[i] = (A[i] - h[i - 1] * z[i - 1]) / l[i];
		}

		l[n] = 1;
		z[n] = 0;
		cZ[n] = 0;

		for (int j = n - 1; j >= 0; --j)
		{
			cZ[j] = z[j] - u[j] * cZ[j + 1];
			bZ[j] = (dataSet->getDataCoordinate(j + 1).z - dataSet->getDataCoordinate(j).z) / h[j] - h[j] * (cZ[j + 1] + 2 * cZ[j]) / 3;
			dZ[j] = (cZ[j + 1] - cZ[j]) / (3 * h[j]);
		}

		// Interpolation done, check for new zMin zMax
		bin = 0;
		for (float px = 0; px < 1; px += (1.0 / numElem))
		{
			/* check that we are in the correct bin */
			while ((px > dataSet->getDataCoordinate(bin + 1).x))
			{
				bin++;
			}

			/* compute interpolated y value */
			valueInter = dataSet->getDataCoordinate(bin).z +
			             bZ[bin] * (px - dataSet->getDataCoordinate(bin).x) +
			             cZ[bin] * (px - dataSet->getDataCoordinate(bin).x) * (px - dataSet->getDataCoordinate(bin).x) +
			             dZ[bin] * (px - dataSet->getDataCoordinate(bin).x) * (px - dataSet->getDataCoordinate(bin).x) * (px - dataSet->getDataCoordinate(bin).x);

			/* Updated dataSet min/max */
			if (valueInter < zMin)
				zMin = valueInter;
			if (valueInter > zMax)
				zMax = valueInter;
		}
		free(h);
		free(A);
		free(l);
		free(u);
		free(z);
	}
}

#endif //GRAFICI_GFX_DATA_DECORATOR_SPLINE_H
