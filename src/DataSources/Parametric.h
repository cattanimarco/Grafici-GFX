#ifndef GRAFICI_DATASOURCE_PARAMETRIC_H
#define GRAFICI_DATASOURCE_PARAMETRIC_H

#include "../DataSource.h"

namespace DataSources
{

template <typename T>
class Parametric : public DataSources::DataSource<DataNorm>, public RangeOpt<T>
{
  public:
	Parametric(size_t length)
	{
		_length = length;
	}

	DataNorm at(size_t index) const override
	{
		if (index < length())
		{
			return RangeOpt<T>::range.normalize(valueAt(index));
		}
		else
		{
			return 0;
		}
	}

	virtual T valueAt(size_t index) const = 0;

  protected:
	/* provide obvious implementation that iterates over all value */
	virtual void computeLimits()
	{
		if (length() > 0)
		{
			RangeOpt<T>::range = { valueAt(0), valueAt(0) };
			for (size_t idx = 1; idx < length(); ++idx)
			{
				RangeOpt<T>::range.update(valueAt(idx));
			}
		}
	}
};

} // namespace DataSources

#endif /* GRAFICI_DATASOURCE_PARAMETRIC_H */
