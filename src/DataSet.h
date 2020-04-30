#ifndef GRAFICI_DATASET_BASE_H
#define GRAFICI_DATASET_BASE_H


#include "DataSource.h"
#include "DataVector.h"

namespace DataSet
{
class Base : public DataSource::Base<DataVector<DataNorm>>
{
  public:
	Base(DataSource::Base<DataNorm> &x, DataSource::Base<DataNorm> &y, DataSource::Base<DataNorm> &c, DataSource::Base<DataNorm> &opt)
	    : _x{ x }
	    , _y{ y }
	    , _c{ c }
	    , _opt{ opt }
	{
		refresh();
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
	};

	size_t &length() override
	{
		return _length;
	};

	void refresh() override
	{
		_x.refresh();
		_y.refresh();
		_c.refresh();
		_opt.refresh();
		_length = sourceLength();
	};

  protected:
  
	size_t sourceLength() const
	{
		/* TODO warning if lengths are different */
		size_t len = _x.length();
		len = graficiMin<size_t>(len, _y.length());
		len = graficiMin<size_t>(len, _c.length());
		len = graficiMin<size_t>(len, _opt.length());
		return len;
	};

	DataSource::Base<DataNorm> &_x;
	DataSource::Base<DataNorm> &_y;
	DataSource::Base<DataNorm> &_c;
	DataSource::Base<DataNorm> &_opt;
};
} // namespace DataSet

#endif //GRAFICI_DATASET_BASE_H
