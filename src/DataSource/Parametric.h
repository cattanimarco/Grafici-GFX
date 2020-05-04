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

class Linear : public Parametric<int>
{
  public:
	Linear(size_t length, int offset = 0, int slope = 1)
	    : Parametric{ length }
	    , _offset{ offset }
	    , _slope{ slope }
	{
		refresh();
	}

	int valueAt(size_t index) const override
	{
		return (index - _offset) * _slope;
	}

	void refresh() override
	{
		_limits = { valueAt(0), valueAt(0) };
		_limits.update(valueAt(length() - 1));
	}

  private:
	int _offset;
	int _slope;
};

class BarIndex : public Parametric<double>
{
  public:
	BarIndex(size_t length)
	    : Parametric{ length }
	{
		refresh();
	}

	double valueAt(size_t index) const override
	{
		return 0.5 + index;
	}

	void refresh() override
	{
		_limits = { 0.0, static_cast<double>(_length)};
	}
};

class Constant : public Parametric<double>
{
  public:
	Constant(size_t length, double value)
	    : Parametric{ length }
	    , _value{ value }
	{
		_limits = { 0.0, 1.0 };
	}

	double valueAt(size_t index __attribute__((unused))) const override
	{
		return _value;
	}

	void refresh() override
	{
	}

  private:
	double _value;
};

}
// DataCoordinate InvertedGenerator(int index)
// {
// 	return 1.0 / index;
// };

#endif /* GRAFICI_DATASOURCE_PARAMETRIC_H */
