#ifndef GRAFICI_DATASET_PARAMETRIC_H
#define GRAFICI_DATASET_PARAMETRIC_H

#include "../Data.h"

// TODO convert to template
typedef DataCoordinate (*DataSourceGenerator)(int index);

class DataSourceParametric : public DataSource
{
  public:
	DataSourceParametric(DataSourceGenerator dataSourceGenerator, int arrayLength);

	DataCoordinate getDataCoordinate(int index) const override;
	void refresh() override;

	FloatLimits dataLimits();
	FloatLimits setDataLimits(FloatLimits limits);

  private:
	FloatLimits limits{ 0, 0 };
	DataSourceGenerator dataSourceGenerator{ nullptr };
};

DataCoordinate LinearGenerator(int index)
{
	return index;
};

DataCoordinate InvertedGenerator(int index)
{
	return 1.0 / index;
};

#endif /* GRAFICI_DATASET_PARAMETRIC_H */
