#ifndef GRAFICI_DATASOURCE_LINEAR_H
#define GRAFICI_DATASOURCE_LINEAR_H

#include "Parametric.h"

namespace DataSource
{
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

}

#endif /* GRAFICI_DATASOURCE_LINEAR_H */
