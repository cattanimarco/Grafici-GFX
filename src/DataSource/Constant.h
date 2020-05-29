#ifndef GRAFICI_DATASOURCE_CONSTANT_H
#define GRAFICI_DATASOURCE_CONSTANT_H

#include "Parametric.h"

namespace DataSource
{

class Constant : public Parametric<double>
{
  public:
	Constant(size_t length, double value)
	    : Parametric{ length }
	    , _value{ graficiTrim(value, { 0.0, 1.0 }) }
	{
		_limits = { 0.0, 1.0 };
	}

	double valueAt(size_t index __attribute__((unused))) const override
	{
		return _value;
	}

  private:
	double _value;
};

} // namespace DataSource

#endif /* GRAFICI_DATASOURCE_CONSTANT_H */
