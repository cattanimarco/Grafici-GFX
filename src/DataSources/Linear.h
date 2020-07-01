#ifndef GRAFICI_DATASOURCE_LINEAR_H
#define GRAFICI_DATASOURCE_LINEAR_H

#include "Parametric.h"

namespace DataSources
{
class Linear : public Parametric<float>
{
  public:
	Linear(size_t length, float offset = 0, float slope = 1)
	    : Parametric{ length }
	    , _offset{ offset }
	    , _slope{ slope }
	{
		computeLimits();
	}

	float valueAt(size_t index) const override
	{
		return (index - _offset) * _slope;
	}

  private:
	void computeLimits() override
	{
		range = { valueAt(0), valueAt(0) };
		range.update(valueAt(length() - 1));
	}

	float _offset;
	float _slope;
};

} // namespace DataSources

#endif /* GRAFICI_DATASOURCE_LINEAR_H */
