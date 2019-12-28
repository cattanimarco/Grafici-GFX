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

	DataSetInterpolator interpolatedX() const;
	DataSetInterpolator interpolatedY() const;

  private:
	enum class DatasetSelection
	{
		none,
		x,
		y,
	};
	
	DatasetSelection selectedDataset{ DatasetSelection::none };
	DataSet *dataSetX{ nullptr };
	DataSet *dataSetY{ nullptr };
};

#endif /* GRAFICI_DATASET_INTERPOLATE_H */