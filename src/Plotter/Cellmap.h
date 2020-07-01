#ifndef GRAFICI_GFX_PLOTTER_CELLMAP_H
#define GRAFICI_GFX_PLOTTER_CELLMAP_H

#include "Heatmap.h"

namespace Plotter
{

class Cellmap : public Heatmap
{
  protected:
	float process_cell(Range<DataNorm> x, Range<DataNorm> y, const DataSets::DataSet &data) const override
	{
		/* search for the two closest data points */
		float cell_value = 0.0;
		float minDistance[2]{ 2.0, 0.0 };
		for (auto it = data.begin(); it != data.end(); it++)
		{
			auto dataPoint = *it;
			float dx = pow(dataPoint.x() - x.mid(), 2);
			float dy = pow(dataPoint.y() - y.mid(), 2);
			float distance = sqrt(dx + dy);
			if (distance < minDistance[0])
			{
				minDistance[1] = minDistance[0];
				minDistance[0] = distance;
			}
		}
		merge_distance(cell_value, minDistance[1] - minDistance[0]);
		return cell_value;
	}

	void merge_distance(float &cell_value, float distance) const override
	{
		/* Clip distance using the treshold */
		if (distance > CELLMAP_TRESHOLD)
		{
			distance = CELLMAP_TRESHOLD;
		}
		cell_value = CELLMAP_TRESHOLD / (distance + CELLMAP_TRESHOLD);
	}
};

} // namespace Plotter
#endif //GRAFICI_GFX_PLOTTER_CELLMAP_H
