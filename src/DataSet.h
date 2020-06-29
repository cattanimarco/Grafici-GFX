#ifndef GRAFICI_DATASET_BASE_H
#define GRAFICI_DATASET_BASE_H

#include "DataSource.h"
#include "DataVector.h"

namespace DataSets
{
class DataSet : public DataSources::DataSource<DataVector<DataNorm>>
{
  public:
	DataSet(const DataSources::DataSource<DataNorm> &x, const DataSources::DataSource<DataNorm> &y, const DataSources::DataSource<DataNorm> &c, const DataSources::DataSource<DataNorm> &opt)
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

	const DataSources::DataSource<DataNorm> &_x;
	const DataSources::DataSource<DataNorm> &_y;
	const DataSources::DataSource<DataNorm> &_c;
	const DataSources::DataSource<DataNorm> &_opt;
};
} // namespace DataSets

#endif //GRAFICI_DATASET_BASE_H
