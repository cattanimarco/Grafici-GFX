#ifndef GRAFICI_DATASET_HISTOGRAM_H
#define GRAFICI_DATASET_HISTOGRAM_H

#include "../Data.h"

class DataSetHistogram : public DataSet
{
  public:
	DataSetHistogram(DataSet &dataSet, int buckets);

	DataCoordinate getDataCoordinate(int index) override;
	void refresh() override;

	FloatLimits dataLimits();
	FloatLimits dataLimits(FloatLimits limits);

  private:
	IntLimits limits{ 0, 0 };
	DataSet *dataSet{ nullptr };
	int *buckets{ nullptr };
};

#endif //GRAFICI_DATASET_HISTOGRAM_H
