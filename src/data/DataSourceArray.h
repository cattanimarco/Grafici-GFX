#ifndef GRAFICI_DATA_SOURCE_ARRAY_H
#define GRAFICI_DATA_SOURCE_ARRAY_H

#include "../Data.h"

template <typename T>
class DataSourceArray : public DataSource<T>
{
  public:
	void begin(T *dataArray, size_t arrayLength)
	{
		_dataArray = dataArray;
		DataSource<T>::length() = arrayLength;
		refresh();
	};

	DataNorm at(size_t index) const override
	{
		if ((_dataArray != nullptr) && (index < DataSource<T>::length()))
		{
			/* normalize DataCoordinate against the _limits range */
			return _limits.normalize(_dataArray[index]);
		}
		else
		{
			return T{ 0 };
		}
	};

	void refresh() override
	{
		if ((_dataArray != nullptr) && (DataSource<T>::length() > 0))
		{
			_limits.min() = _limits.max() = _dataArray[0];
			for (size_t i = 1; i < DataSource<T>::length(); ++i)
			{
				_limits.min() = graficiMin<T>(_limits.min(), _dataArray[i]);
				_limits.max() = graficiMax<T>(_limits.max(), _dataArray[i]);
			}
		}
		else
		{
			_limits = { 0, 0 };
		}
	};

	Range<T> &dataLimits()
	{
		return _limits;
	};

  private:
	Range<T> _limits{ 0, 0 };
	T *_dataArray{ nullptr };
};

#endif /* GRAFICI_DATA_SOURCE_ARRAY_H */
