#include "DataSourceSpline.h"

DataSourceSpline::DataSourceSpline(DataSource &dataSourceX, DataSource &dataSourceY, int interpolationSteps)
{
	this->dataSourceX = &dataSourceX;
	this->dataSourceY = &dataSourceY;
	setLength(interpolationSteps);

	//TODO make sure x axis is in increasing order

	// Note thar refresh also allocate new memory the first time it is invoked
	refresh();
}

DataSourceSpline::~DataSourceSpline()
{
	free(b);
	free(c);
	free(d);
}

DataCoordinate DataSourceSpline::getDataCoordinate(int index) const
{
	if (SelectedDataSource::none == selectedDataSource)
	{
		return DataCoordinate{ 0 };
	}

	if (index < length())
	{
		int bin = 0;
		DataCoordinate x = (1.0 * index) / (length() - 1);

		if (SelectedDataSource::x == selectedDataSource)
		{
			return x;
		}

		// check that we are in the correct bin
		while (x > dataSourceX->getDataCoordinate(bin + 1))
		{
			bin++;
			if (bin == dataSourceX->length())
			{
				bin--;
				break;
			}
		}

		// compute interpolated y
		DataCoordinate y = dataSourceY->getDataCoordinate(bin) +
		                   b[bin] * (x - dataSourceX->getDataCoordinate(bin)) +
		                   c[bin] * (x - dataSourceX->getDataCoordinate(bin)) * (x - dataSourceX->getDataCoordinate(bin)) +
		                   d[bin] * (x - dataSourceX->getDataCoordinate(bin)) * (x - dataSourceX->getDataCoordinate(bin)) * (x - dataSourceX->getDataCoordinate(bin));

		// normalize dataSource to a 0.0 .. 1.0 value
		return DataCoordinate{ (y - limits.low) / (limits.high - limits.low) };
	}
	else
	{
		return DataCoordinate{ 0 };
	}
}

void DataSourceSpline::refresh(void)
{
	dataSourceX->refresh();
	dataSourceY->refresh();

	// compute spline parameter, than scan all x values to find new min max
	if (this->length() >= dataSourceX->length())
	{
		int bin = 0;
		const int n = (dataSourceX->length() - 1);
		DataCoordinate yInter;

		limits = { 1, 0 };

		free(b);
		free(c);
		free(d);

		b = static_cast<DataCoordinate *>(malloc(sizeof(DataCoordinate) * n + 1));
		c = static_cast<DataCoordinate *>(malloc(sizeof(DataCoordinate) * n + 1));
		d = static_cast<DataCoordinate *>(malloc(sizeof(DataCoordinate) * n + 1));

		DataCoordinate *h = static_cast<DataCoordinate *>(malloc(sizeof(DataCoordinate) * n));
		DataCoordinate *A = static_cast<DataCoordinate *>(malloc(sizeof(DataCoordinate) * n));
		DataCoordinate *l = static_cast<DataCoordinate *>(malloc(sizeof(DataCoordinate) * n + 1));
		DataCoordinate *u = static_cast<DataCoordinate *>(malloc(sizeof(DataCoordinate) * n + 1));
		DataCoordinate *z = static_cast<DataCoordinate *>(malloc(sizeof(DataCoordinate) * n + 1));

		for (int i = 0; i <= n - 1; ++i)
		{
			h[i] = dataSourceX->getDataCoordinate(i + 1) - dataSourceX->getDataCoordinate(i);
		}

		// Interpolate Y axis
		for (int i = 1; i <= n - 1; ++i)
		{
			A[i] = 3 * (dataSourceY->getDataCoordinate(i + 1) - dataSourceY->getDataCoordinate(i)) / h[i] - 3 * (dataSourceY->getDataCoordinate(i) - dataSourceY->getDataCoordinate(i - 1)) / h[i - 1];
		}

		l[0] = 1;
		u[0] = 0;
		z[0] = 0;

		for (int i = 1; i <= n - 1; ++i)
		{
			l[i] = 2 * (dataSourceX->getDataCoordinate(i + 1) - dataSourceX->getDataCoordinate(i - 1)) - h[i - 1] * u[i - 1];
			u[i] = h[i] / l[i];
			z[i] = (A[i] - h[i - 1] * z[i - 1]) / l[i];
		}

		l[n] = 1;
		z[n] = 0;
		c[n] = 0;

		for (int j = n - 1; j >= 0; --j)
		{
			c[j] = z[j] - u[j] * c[j + 1];
			b[j] = (dataSourceY->getDataCoordinate(j + 1) - dataSourceY->getDataCoordinate(j)) / h[j] - h[j] * (c[j + 1] + 2 * c[j]) / 3;
			d[j] = (c[j + 1] - c[j]) / (3 * h[j]);
		}

		// Interpolation done, check for new yMin yMax
		bin = 0;
		for (float px = 0; px < 1; px += (1.0 / this->length()))
		{
			/* check that we are in the correct bin */
			while (px > dataSourceX->getDataCoordinate(bin + 1))
			{
				bin++;
			}

			/* compute interpolated y value */
			yInter = dataSourceY->getDataCoordinate(bin) +
			         b[bin] * (px - dataSourceX->getDataCoordinate(bin)) +
			         c[bin] * (px - dataSourceX->getDataCoordinate(bin)) * (px - dataSourceX->getDataCoordinate(bin)) +
			         d[bin] * (px - dataSourceX->getDataCoordinate(bin)) * (px - dataSourceX->getDataCoordinate(bin)) * (px - dataSourceX->getDataCoordinate(bin));

			/* Updated dataSource min/max */
			if (yInter < limits.low)
				limits.low = yInter;
			if (yInter > limits.high)
				limits.high = yInter;
		}

		free(h);
		free(A);
		free(l);
		free(u);
		free(z);
	}
}
