#ifndef GRAFICI_DATASET_HISTOGRAM_H
#define GRAFICI_DATASET_HISTOGRAM_H

#include "../Data.h"

class DataSourceHistogram : public DataSource
{
  public:
	DataSourceHistogram(DataSource &dataSource, int buckets);

	DataCoordinate getDataCoordinate(int index) const override;
	void refresh() override;

	IntLimits dataLimits();
	IntLimits setDataLimits(IntLimits limits);

  private:
	IntLimits limits{ 0, 0 };
	DataSource *dataSource{ nullptr };
	int *buckets{ nullptr };
};

#endif //GRAFICI_DATASET_HISTOGRAM_H
