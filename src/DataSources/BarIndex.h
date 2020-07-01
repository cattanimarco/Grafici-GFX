#ifndef GRAFICI_DATASOURCE_BARINDEX_H
#define GRAFICI_DATASOURCE_BARINDEX_H

#include "Parametric.h"

namespace DataSources
{

class BarIndex : public Parametric<float>
{
  public:
	/* To plot multiple n bar plots, use num_classes = n and use n of this classes for the x axis.
	 Each class with class_id [0, n-1] */
	BarIndex(size_t length, size_t class_id = 0, size_t num_classes = 1)
	    : Parametric{ length }
	    , _num_classes{ num_classes }
	    , _class_id{ class_id }
	{
		computeLimits();
	}

	float valueAt(size_t index) const override
	{
		return 0.5 + index * _num_classes + _class_id;
	}

  private:
	void computeLimits() override
	{
		range = { 0.0, static_cast<float>(_length * _num_classes) };
	}

	size_t _num_classes;
	size_t _class_id;
};

} // namespace DataSources

#endif /* GRAFICI_DATASOURCE_BARINDEX_H */
