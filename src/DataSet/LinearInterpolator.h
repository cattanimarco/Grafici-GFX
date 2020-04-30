#ifndef GRAFICI_DATASET_LINEAR_INTERPOLATOR_H
#define GRAFICI_DATASET_LINEAR_INTERPOLATOR_H

#include "../DataSet.h"
#include "../DataSource/Select.h"

namespace DataSet
{

class LinearInterpolator : public Base
{
  public:
	LinearInterpolator(DataSource::Base<DataNorm> &x, DataSource::Base<DataNorm> &y, DataSource::Base<DataNorm> &c, DataSource::Base<DataNorm> &opt, size_t interpolationSteps)
	    : Base(x, y, c, opt)
	{
		//make sure interpolationSteps > _length?
		_sourceLength = _length;
		_length = interpolationSteps;
	}

	DataVector<DataNorm> at(size_t index) const override
	{
		DataVector<DataNorm> result{ 0.0, 0.0, 0.0, 0.0 };

		if (index < length())
		{
			size_t bin = 0;
			result.x() = (1.0 * index) / (length() - 1);

			// compute in which x bin we are
			while (result.x() > _x.at(bin + 1))
			{
				bin++;
				// we stop at _sourceLength as it is the minimum length among the datasources (computed by Base::refresh())
				// this way we are sure we do not overflow on y c and opt
				if (bin == _sourceLength)
				{
					bin--;
					break;
				}
			}

			/* Compute the normal interpolation for x */
			Range<DataNorm> rangeX{ _x.at(bin), _x.at(bin + 1) };
			double interpolationNorm = rangeX.normalize(result.x());

			/* Use the normal interpolation for x to map the other datasources */
			Range<DataNorm> rangeY{ _y.at(bin), _y.at(bin + 1) };
			Range<DataNorm> rangeC{ _c.at(bin), _c.at(bin + 1) };
			Range<DataNorm> rangeOpt{ _opt.at(bin), _opt.at(bin + 1) };
			result.y() = rangeY.map(interpolationNorm);
			result.c() = rangeC.map(interpolationNorm);
			result.opt() = rangeOpt.map(interpolationNorm);
		}
		return result;
	};

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
	};

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
	size_t _sourceLength;
};

} // namespace DataSet

#endif /* GRAFICI_DATASET_LINEAR_INTERPOLATOR_H */