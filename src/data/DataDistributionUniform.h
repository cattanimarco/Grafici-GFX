#ifndef GRAFICI_DATA_DIST_UNIFORM_H
#define GRAFICI_DATA_DIST_UNIFORM_H

#include "DataParametric.h"


template<size_t N>
class DataDistributionUniform : public DataParametric
{
  public:
    /* approximate normal distribution using Box-Muller transform */
	DataDistributionUniform(unsigned long seed, Range<float> range = {0,1})
	    : DataParametric{ N, range }
	{
		init_distribution(seed);
	}

  protected:
	float at(size_t idx) const override
	{
		return uniform_data[idx];
	}

  private:

	static const long precision = 100;

	void init_distribution(unsigned long seed)
	{
		randomSeed(seed);
		for (size_t i = 0; i < N; ++i) 
		{
			uniform_data[i] =  random(0,precision+1) / (float)precision;
		}
	}
	
	float uniform_data[N];
};

#endif /* GRAFICI_DATA_DIST_UNIFORM_H */

/** @}*/