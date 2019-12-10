#ifndef GRAFICI_DATASET_INTERPOLATE_H
#define GRAFICI_DATASET_INTERPOLATE_H

#include "../Data.h"
#include "DataSetParametric.h"

class DataSetInterpolator : public DataSet
{
  public:
	DataSetInterpolator(DataSet &dataSetX, DataSet &dataSetY, int interpolationSteps);

	DataCoordinate getDataCoordinate(int index) const override;
	void refresh() override;

	// FloatLimits dataLimitsX();
	// FloatLimits setDataLimitsX(FloatLimits limits);
	// FloatLimits dataLimitsY();
	// FloatLimits setDataLimitsY(FloatLimits limits);

	DataSetParametric dataSetX;
	DataSetParametric dataSetY;

  private:
	DataCoordinate generatorX(int index);
	DataCoordinate generatorY(int index);

	FloatLimits limits{ 0, 0 };
	DataSet *dataSetInX{ nullptr };
	DataSet *dataSetInY{ nullptr };
};

#endif /* GRAFICI_DATASET_INTERPOLATE_H */