#ifndef GRAFICI_DATASET_SPLINE_INTERPOLATOR_H
#define GRAFICI_DATASET_SPLINE_INTERPOLATOR_H

#include "LinearInterpolator.h"

namespace DataSets
{

class SplineInterpolator : public LinearInterpolator
{
  public:
	SplineInterpolator(DataSources::DataSource<DataNorm> &x, DataSources::DataSource<DataNorm> &y, DataSources::DataSource<DataNorm> &c, DataSources::DataSource<DataNorm> &opt, size_t interpolationSteps)
	    : LinearInterpolator(x, y, c, opt, interpolationSteps)
	{
		_computeSpline(_y, _ySpline);
	}

	~SplineInterpolator()
	{
		free(_ySpline.b);
		free(_ySpline.c);
		free(_ySpline.d);
		// free(_cSpline.b);
		// free(_cSpline.c);
		// free(_cSpline.d);
		// free(_optSpline.b);
		// free(_optSpline.c);
		// free(_optSpline.d);
	}

	DataVector<DataNorm> at(size_t index) const override
	{
		DataVector<DataNorm> result = LinearInterpolator::at(index);
		if (index < length())
		{
			result.y() = _interpolatedIndex(_y, _ySpline, index);
			//result.c() = _interpolatedIndex(_c, _cSpline, index);
			//result.opt() = _interpolatedIndex(_opt, _optSpline, index);
		}
		return result;
	}

  private:
	struct SplineData
	{
		Range<DataNorm> limits{ 1, 0 };
		DataNorm *b{ nullptr };
		DataNorm *c{ nullptr };
		DataNorm *d{ nullptr };
	};

	DataNorm _interpolatedValue(const DataSources::DataSource<DataNorm> &source, const SplineData &splineData, const float x) const
	{
		size_t bin = 0;
		/* Search in which x bin the datapoint is */
		while (x > _x.at(bin + 1))
		{
			bin++;
			if (bin == _sourceLength)
			{
				bin--;
				break;
			}
		}

		/* interpolate source using splineData's spline values */
		DataNorm value = source.at(bin) +
		                 splineData.b[bin] * (x - _x.at(bin)) +
		                 splineData.c[bin] * (x - _x.at(bin)) * (x - _x.at(bin)) +
		                 splineData.d[bin] * (x - _x.at(bin)) * (x - _x.at(bin)) * (x - _x.at(bin));
		return value;
	}

	DataNorm _interpolatedIndex(const DataSources::DataSource<DataNorm> &source, const SplineData &splineData, const size_t index) const
	{
		DataNorm value = _interpolatedValue(source, splineData, _indexToX(index));
		return splineData.limits.normalize(value);
	}

	void _splineData(const DataSources::DataSource<DataNorm> &source, SplineData &splineData)
	{
		if (length() >= _sourceLength)
		{
			const int n = (_sourceLength - 1);

			free(splineData.b);
			free(splineData.c);
			free(splineData.d);

			splineData.b = static_cast<DataNorm *>(malloc(sizeof(DataNorm) * n + 1));
			splineData.c = static_cast<DataNorm *>(malloc(sizeof(DataNorm) * n + 1));
			splineData.d = static_cast<DataNorm *>(malloc(sizeof(DataNorm) * n + 1));

			DataNorm *h = static_cast<DataNorm *>(malloc(sizeof(DataNorm) * n));
			DataNorm *A = static_cast<DataNorm *>(malloc(sizeof(DataNorm) * n));
			DataNorm *l = static_cast<DataNorm *>(malloc(sizeof(DataNorm) * n + 1));
			DataNorm *u = static_cast<DataNorm *>(malloc(sizeof(DataNorm) * n + 1));
			DataNorm *z = static_cast<DataNorm *>(malloc(sizeof(DataNorm) * n + 1));

			// compute deltas
			for (int i = 0; i <= n - 1; ++i)
			{
				h[i] = _x.at(i + 1) - _x.at(i);
			}

			// Interpolate Y axis
			for (int i = 1; i <= n - 1; ++i)
			{
				A[i] = 3 * (source.at(i + 1) - source.at(i)) / h[i] - 3 * (source.at(i) - source.at(i - 1)) / h[i - 1];
			}

			l[0] = 1;
			u[0] = 0;
			z[0] = 0;

			for (int i = 1; i <= n - 1; ++i)
			{
				l[i] = 2 * (_x.at(i + 1) - _x.at(i - 1)) - h[i - 1] * u[i - 1];
				u[i] = h[i] / l[i];
				z[i] = (A[i] - h[i - 1] * z[i - 1]) / l[i];
			}

			l[n] = 1;
			z[n] = 0;
			splineData.c[n] = 0;

			for (int j = n - 1; j >= 0; --j)
			{
				splineData.c[j] = z[j] - u[j] * splineData.c[j + 1];
				splineData.b[j] = (source.at(j + 1) - source.at(j)) / h[j] - h[j] * (splineData.c[j + 1] + 2 * splineData.c[j]) / 3;
				splineData.d[j] = (splineData.c[j + 1] - splineData.c[j]) / (3 * h[j]);
			}

			free(h);
			free(A);
			free(l);
			free(u);
			free(z);
		}
	}

	void _computeSpline(const DataSources::DataSource<DataNorm> &source, SplineData &splineData)
	{
		/* compute spline parameter, than scan all x values to find new min max */
		if (length() >= _sourceLength)
		{
			_splineData(source, splineData);

			/* we only change the limits if the interpolation overflows the 0-1 range */
			splineData.limits = { 0, 1 };
			for (double x = 0; x < 1; x += (1.0 / length()))
			{
				/* update splineData min/max */
				splineData.limits.update(_interpolatedValue(source, splineData, x));
			}
		}
	}

	SplineData _ySpline;
	//SplineData _cSpline;
	//SplineData _optSpline;
};

} // namespace DataSets
#endif //GRAFICI_DATASET_SPLINE_INTERPOLATOR_H
