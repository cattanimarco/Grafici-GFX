#ifndef GRAFICI_DATASET_FLOAT_H
#define GRAFICI_DATASET_FLOAT_H

#include "../Data.h"

class DataSourceFloat : public DataSource
{
  public:
	DataSourceFloat(float *floatArray, int arrayLength);

	DataCoordinate getDataCoordinate(int index) const override;
	void refresh() override;

	FloatLimits dataLimits();
	FloatLimits setDataLimits(FloatLimits limits);

  private:
	FloatLimits limits{ 0, 0 };
	float *floatArray{ nullptr };
};

#endif /* GRAFICI_DATASET_FLOAT_H */
