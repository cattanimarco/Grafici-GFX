#ifndef GRAFICI_DATASET_PARAMETRIC_H
#define GRAFICI_DATASET_PARAMETRIC_H

#include "../Data.h"

// TODO convert to template
typedef DataCoordinate (*DataSetGenerator)(int index);

class DataSetParametric : public DataSet
{
  public:
	DataSetParametric(DataSetGenerator dataSetGenerator, int arrayLength);

	DataCoordinate getDataCoordinate(int index) const override;
	void refresh() override;

	FloatLimits dataLimits();
	FloatLimits setDataLimits(FloatLimits limits);

  private:
	FloatLimits limits{ 0, 0 };
	DataSetGenerator dataSetGenerator{ nullptr };
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
