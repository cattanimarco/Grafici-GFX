#ifndef GRAFICI_DATASET_INTERPOLATOR_H
#define GRAFICI_DATASET_INTERPOLATOR_H

#include "../Data.h"

class DataSourceInterpolator : public DataSourceTuple
{
  public:
	DataSourceInterpolator(DataSource &dataSourceX, DataSource &dataSourceY, int interpolationSteps);

	DataCoordinate getDataCoordinate(int index) const override;
	void refresh() override;

	DataSource DataSourceX() const override;
	DataSource DataSourceY() const override;
};

#endif /* GRAFICI_DATASET_INTERPOLATOR_H */