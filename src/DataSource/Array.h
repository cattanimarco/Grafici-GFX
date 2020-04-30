#ifndef GRAFICI_DATASOURCE_ARRAY_H
#define GRAFICI_DATASOURCE_ARRAY_H

#include "../DataSource.h"

namespace DataSource
{

template <typename T>
class Array : public DataSource::Base<DataNorm>
{
  public:
	Array(T *data, size_t length)
	    : _dataArray{ data }

	{
		_length = length;
		refresh();
	};

	DataNorm at(size_t index) const override
	{
		if ((_dataArray != nullptr) && (index < length()))
		{
			/* normalize DataCoordinate against the _limits range */
			return _limits.normalize(_dataArray[index]);
		}
		else
		{
			return 0;
		}
	};

	void refresh() override
	{
		if ((_dataArray != nullptr) && (length() > 0))
		{
			_limits = { _dataArray[0], _dataArray[0] };
			for (size_t idx = 1; idx < length(); ++idx)
			{
				_limits.update(_dataArray[idx]);
			}
		}
		else
		{
			_limits = { 0, 0 };
		}
	};

	Range<T> &limits()
	{
		return _limits;
	};

  private:
	Range<T> _limits{ 0, 0 };
	T *_dataArray{ nullptr };
};

}
#endif /* GRAFICI_DATASOURCE_ARRAY_H */
