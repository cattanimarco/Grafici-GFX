#ifndef GRAFICI_DATA_DIST_NORMAL_H
#define GRAFICI_DATA_DIST_NORMAL_H

#include "DataParametric.h"

static float generateGaussian(float mean, float stdDev) {
    static float spare;
    static bool hasSpare = false;
	static const long precision = 1000;

    if (hasSpare) {
        hasSpare = false;
        return spare * stdDev + mean;
    } else {
        float u, v, s;
        do {
            u = (random(0,precision+1) / (float)precision) * 2.0 - 1.0;
            v = (random(0,precision+1) / (float)precision) * 2.0 - 1.0;
            s = u * u + v * v;
        } while (s >= 1.0 || s == 0.0);
        s = sqrt(-2.0 * log(s) / s);
        spare = v * s;
        hasSpare = true;
        return mean + stdDev * u * s;
    }
}

template<size_t N>
class DataDistributionNormal : public DataParametric
{
  public:
    /* approximate normal distribution using Box-Muller transform */
	DataDistributionNormal(unsigned long seed, Range<float> range = {0,1})
	    : DataParametric{ N, range }
	{
		init_distribution(seed);
	}

  protected:
	float at(size_t idx) const override
	{
		return normal_data[idx];
	}

  private:

	static const long precision = 100;

	void init_distribution(unsigned long seed)
	{
		randomSeed(seed);
		for (size_t i = 0; i < N; ++i) 
		{
			// https://www.wolframalpha.com/input?i=gaussian+with+mean+%3D+0.5+and+deviation+%3D+0.2
			normal_data[i] =  generateGaussian(0.5,0.2);
		}
	}

	float normal_data[N];
};

#endif /* GRAFICI_DATA_DIST_NORMAL_H */

/** @}*/