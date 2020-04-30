#ifndef GRAFICI_DATASET_SPLINE_INTERPOLATOR_H
#define GRAFICI_DATASET_SPLINE_INTERPOLATOR_H

#include "../DataSet.h"
#include "../DataSource/Select.h"

namespace DataSet
{

class SplineInterpolator : public Base
{
  public:
	SplineInterpolator(DataSource::Base<DataNorm> &x, DataSource::Base<DataNorm> &y, DataSource::Base<DataNorm> &c, DataSource::Base<DataNorm> &opt, size_t interpolationSteps)
	    : Base(x, y, c, opt)
	{
		// TODO make sure interpolationSteps > _length?
		// TODO make sure x axis is in increasing order
		_sourceLength = _length;
		_length = interpolationSteps;
		refresh();
	}

	~SplineInterpolator()
	{
		free(_ySpline.b);
		free(_ySpline.c);
		free(_ySpline.d);
		free(_cSpline.b);
		free(_cSpline.c);
		free(_cSpline.d);
		free(_optSpline.b);
		free(_optSpline.c);
		free(_optSpline.d);
	}

	DataVector<DataNorm> at(size_t index) const override
	{

		DataVector<DataNorm> result{ 0.0, 0.0, 0.0, 0.0 };

		if (index < length())
		{
			result.x() = _indexToX(index);
			result.y() = _interpolatedIndex(_y, _ySpline, index);
			result.c() = _interpolatedIndex(_c, _cSpline, index);
			result.opt() = _interpolatedIndex(_opt, _optSpline, index);
		}
		return result;
	}

	size_t &length() override
	{
		return _length;
	};

	const size_t &length() const override
	{
		return _length;
	};

	void refresh() override
	{
		/* we save the interpolation steps as the base refresh override the _length value */
		auto interpolationSteps = _length;
		Base::refresh();
		_sourceLength = _length;
		_length = interpolationSteps;

		/* compute spline params for y, c, and opt channels */
		_refresh(_y, _ySpline);
		_refresh(_c, _cSpline);
		_refresh(_opt, _optSpline);
	}

	/* methods to get a datasource from the interpolated dataset */
	DataSource::Select x() const
	{
		return DataSource::Select(*this, DataSource::Channel::x);
	}
	DataSource::Select y() const
	{
		return DataSource::Select(*this, DataSource::Channel::y);
	}
	DataSource::Select c() const
	{
		return DataSource::Select(*this, DataSource::Channel::c);
	}
	DataSource::Select opt() const
	{
		return DataSource::Select(*this, DataSource::Channel::opt);
	}

  private:
	struct _SplineData
	{
		Range<DataNorm> limits{ 1, 0 };
		DataNorm *b{ nullptr };
		DataNorm *c{ nullptr };
		DataNorm *d{ nullptr };
	};

	DataNorm _interpolatedValue(const DataSource::Base<DataNorm> &source, const _SplineData &splineData, const double x) const
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

	DataNorm _indexToX(const size_t index) const
	{
		return (1.0 * index) / (length() - 1);
	}

	DataNorm _interpolatedIndex(const DataSource::Base<DataNorm> &source, const _SplineData &splineData, const size_t index) const
	{
		DataNorm value = _interpolatedValue(source, splineData, _indexToX(index));
		return splineData.limits.normalize(value);
	}

	void _splineData(const DataSource::Base<DataNorm> &source, _SplineData &splineData)
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

	void _refresh(const DataSource::Base<DataNorm> &source, _SplineData &splineData)
	{
		/* compute spline parameter, than scan all x values to find new min max */
		if (length() >= _sourceLength)
		{
			_splineData(source, splineData);

			splineData.limits = { 1, 0 };
			for (double x = 0; x < 1; x += (1.0 / length()))
			{
				/* update splineData min/max */
				splineData.limits.update(_interpolatedValue(source, splineData, x));
			}
		}
	}

	_SplineData _ySpline;
	_SplineData _cSpline;
	_SplineData _optSpline;
	size_t _sourceLength;
};

} // namespace DataSet
#endif //GRAFICI_DATASET_SPLINE_INTERPOLATOR_H
