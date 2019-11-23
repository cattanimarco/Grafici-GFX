#ifndef GRAFICI_DATASET_PARAMETRIC_H
#define GRAFICI_DATASET_PARAMETRIC_H

#include "../Data.h"

// TODO convert to template

float LinearGenerator(int index)
{
	return index;
};

float InvertedGenerator(int index)
{
	return 1.0 / index;
};

class DataSetParametric : public DataSet
{
  public:
	typedef float (*DataSetGenerator)(int index);

	DataSetParametric(DataSetGenerator dataSetGenerator, int arrayLength);

	DataCoordinate getDataCoordinate(int index) override;
	void refresh() override;

	FloatLimits dataLimits();
	FloatLimits dataLimits(FloatLimits limits);

  private:
	FloatLimits limits{ 0, 0 };
	DataSetGenerator dataSetGenerator{ nullptr };
};

#endif /* GRAFICI_DATASET_PARAMETRIC_H */
