#ifndef GRAFICI_DATASOURCE_PARAMETRIC_H
#define GRAFICI_DATASOURCE_PARAMETRIC_H

#include "../DataSource.h"

namespace DataSource
{

template <typename T>
class Parametric : public DataSource::Base<DataNorm>
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
			return _limits.normalize(valueAt(index));
		}
		else
		{
			return 0;
		}
	}

	virtual T valueAt(size_t index) const = 0;

	/* provide obvious implementation that iterates over all value */
	virtual void refresh() override
	{
		if (length() > 0)
		{
			_limits = { valueAt(0), valueAt(0) };
			for (size_t idx = 1; idx < length(); ++idx)
			{
				_limits.update(valueAt(idx));
			}
		}
		else
		{
			_limits = { 0, 0 };
		}
	}

	Range<T> &limits()
	{
		return _limits;
	};

  protected:
	Range<T> _limits{ 0, 0 };
};

}

#endif /* GRAFICI_DATASOURCE_PARAMETRIC_H */
