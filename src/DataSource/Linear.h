#ifndef GRAFICI_DATASOURCE_LINEAR_H
#define GRAFICI_DATASOURCE_LINEAR_H

#include "Parametric.h"

namespace DataSource
{
class Linear : public Parametric<double>
{
  public:
	Linear(size_t length, double offset = 0, double slope = 1)
	    : Parametric{ length }
	    , _offset{ offset }
	    , _slope{ slope }
	{
		computeLimits();
	}

	double valueAt(size_t index) const override
	{
		return (index - _offset) * _slope;
	}

  private:
	void computeLimits() override
	{
		_limits = { valueAt(0), valueAt(0) };
		_limits.update(valueAt(length() - 1));
	}

	double _offset;
	double _slope;
};

} // namespace DataSource

#endif /* GRAFICI_DATASOURCE_LINEAR_H */
