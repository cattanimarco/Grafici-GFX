#ifndef GRAFICI_DATASOURCE_CONSTANT_H
#define GRAFICI_DATASOURCE_CONSTANT_H

#include "Parametric.h"

namespace DataSources
{

class Constant : public Parametric<float>
{
  public:
	Constant(size_t length, float value)
	    : Parametric{ length }
	    , _value{ graficiTrim(value, { 0.0, 1.0 }) }
	{
		range = { 0.0, 1.0 };
	}

	float valueAt(size_t index __attribute__((unused))) const override
	{
		return _value;
	}

  private:
	float _value;
};

} // namespace DataSources

#endif /* GRAFICI_DATASOURCE_CONSTANT_H */
