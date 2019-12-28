#ifndef GRAFICI_DATASET_HISTOGRAM_H
#define GRAFICI_DATASET_HISTOGRAM_H

#include "../Data.h"

class DataSetHistogram : public DataSet
{
  public:
	DataSetHistogram(DataSet &dataSet, int buckets);

	DataCoordinate getDataCoordinate(int index) const override;
	void refresh() override;

	IntLimits dataLimits();
	IntLimits setDataLimits(IntLimits limits);

  private:
	IntLimits limits{ 0, 0 };
	DataSet *dataSet{ nullptr };
	int *buckets{ nullptr };
};

#endif //GRAFICI_DATASET_HISTOGRAM_H
