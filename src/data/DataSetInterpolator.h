#ifndef GRAFICI_DATASET_INTERPOLATE_H
#define GRAFICI_DATASET_INTERPOLATE_H

#include "../Data.h"

class DataSetInterpolator : public DataSet
{
  public:
	DataSetInterpolator(DataSet &dataSetX, DataSet &dataSetY, int interpolationSteps);

	DataCoordinates getDataCoordinate(int index) const override;
	void refresh() override;

	FloatLimits dataLimitsX();
	FloatLimits setDataLimitsX(FloatLimits limits);
	FloatLimits dataLimitsY();
	FloatLimits setDataLimitsY(FloatLimits limits);

  private:
	FloatLimits limits{ 0, 0 };
	DataSet *dataSetX{ nullptr };
	DataSet *dataSetY{ nullptr };
};

#endif /* GRAFICI_DATASET_INTERPOLATE_H */