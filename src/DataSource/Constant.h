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

#endif /* GRAFICI_DATASOURCE_CONSTANT_H */
