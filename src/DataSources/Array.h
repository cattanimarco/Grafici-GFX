#ifndef GRAFICI_DATASOURCE_ARRAY_H
#define GRAFICI_DATASOURCE_ARRAY_H

#include "../DataSource.h"

namespace DataSources
{

template <typename T>
class Array : public DataSources::DataSource<DataNorm>
{
  public:
	Array(T *data, size_t length)
	    : _dataArray{ data }

	{
		_length = length;
		computeLimits();
	}

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

	Range<T> &limits()
	{
		return _limits;
	};

	const Range<T> &limits() const
	{
		return _limits;
	};

  private:
	void computeLimits()
	{
		if ((_dataArray != nullptr) && (length() > 0))
		{
			_limits = { _dataArray[0], _dataArray[0] };
			for (size_t idx = 1; idx < length(); ++idx)
			{
				_limits.update(_dataArray[idx]);
			}
		}
	}

	Range<T> _limits{ 0, 0 };
	T *_dataArray{ nullptr };
}; // namespace DataSources

} // namespace DataSources
#endif /* GRAFICI_DATASOURCE_ARRAY_H */
