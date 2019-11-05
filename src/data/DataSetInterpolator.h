#ifndef GRAFICI_DATASET_INTERPOLATE_H
#define GRAFICI_DATASET_INTERPOLATE_H

#include "../Data.h"

class DataSetInterpolator : public DataSet
{
  public:
	DataSetInterpolator(DataSet &dataSet, int interpolationSteps);

	DataCoordinate getDataCoordinate(int index) override;
	void refresh() override;

	FloatLimits dataLimits();
	FloatLimits setDataLimits(FloatLimits limits);

  private:
	FloatLimits limits{ 0, 0 };
	DataSet *dataSet{ nullptr };
};

#endif /* GRAFICI_DATASET_INTERPOLATE_H */