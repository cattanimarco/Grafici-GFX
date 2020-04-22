#ifndef GRAFICI_DATASET_SPLINE_H
#define GRAFICI_DATASET_SPLINE_H

#include "../Data.h"

class DataSourceSpline : public DataSourceTuple
{
  public:
	DataSourceSpline(DataSource &dataSetX, DataSource &dataSetY, int interpolationSteps);
	~DataSourceSpline();

	DataCoordinate at(int index) const override;
	void refresh() override;

	DataSource DataSourceX() const override;
	DataSource DataSourceY() const override;

  private:
	DataCoordinateLimits limits{ 1, 0 };

	//spline support arrays
	DataCoordinate *b{ nullptr };
	DataCoordinate *c{ nullptr };
	DataCoordinate *d{ nullptr };
};

#endif //GRAFICI_DATASET_SPLINE_H
