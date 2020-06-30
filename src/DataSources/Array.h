#ifndef GRAFICI_DATASOURCE_ARRAY_H
#define GRAFICI_DATASOURCE_ARRAY_H

#include "../DataSource.h"

namespace DataSources
{

template <typename T>
class Array : public DataSource<DataNorm>, public Ranged<T>
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
			/* normalize DataCoordinate against the range range */
			return Ranged<T>::range.normalize(_dataArray[index]);
		}
		else
		{
			return 0;
		}
	};

  private:
	void computeLimits()
	{
		if ((_dataArray != nullptr) && (length() > 0))
		{
			Ranged<T>::range = { _dataArray[0], _dataArray[0] };
			for (size_t idx = 1; idx < length(); ++idx)
			{
				Ranged<T>::range.update(_dataArray[idx]);
			}
		}
	}

	T *_dataArray{ nullptr };
}; // namespace DataSources

} // namespace DataSources
#endif /* GRAFICI_DATASOURCE_ARRAY_H */
