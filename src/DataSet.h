#ifndef GRAFICI_DATASET_BASE_H
#define GRAFICI_DATASET_BASE_H

#include "DataSource.h"
#include "DataVector.h"

namespace DataSet
{
class Base : public DataSource::Base<DataVector<DataNorm>>
{
  public:
	Base(const DataSource::Base<DataNorm> &x, const DataSource::Base<DataNorm> &y, const DataSource::Base<DataNorm> &c, const DataSource::Base<DataNorm> &opt)
	    : _x{ x }
	    , _y{ y }
	    , _c{ c }
	    , _opt{ opt }
	{
		_length = computeLength();
	};

	DataVector<DataNorm> at(size_t index) const override
	{
		return DataVector<DataNorm>{
			_x.at(index), _y.at(index), _c.at(index), _opt.at(index)
		};
	}

	const size_t &length() const override
	{
		return _length;
	}

  protected:
	size_t computeLength() const
	{
		/* TODO warning if lengths are different */
		size_t len = _x.length();
		len = graficiMax<size_t>(len, _y.length());
		len = graficiMax<size_t>(len, _c.length());
		len = graficiMax<size_t>(len, _opt.length());
		return len;
	}

	const DataSource::Base<DataNorm> &_x;
	const DataSource::Base<DataNorm> &_y;
	const DataSource::Base<DataNorm> &_c;
	const DataSource::Base<DataNorm> &_opt;
};
} // namespace DataSet

#endif //GRAFICI_DATASET_BASE_H
