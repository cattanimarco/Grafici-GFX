#ifndef GRAFICI_GFX_PLOTTER_HEATMAP_H
#define GRAFICI_GFX_PLOTTER_HEATMAP_H

#include "../Plotter.h"

#ifndef HEATMAP_COLUMNS
#define HEATMAP_COLUMNS 32
#endif

#ifndef HEATMAP_ROWS
#define HEATMAP_ROWS 24
#endif

#ifndef HEATMAP_AUTORANGE
#define HEATMAP_AUTORANGE true
#endif

namespace Plotter
{

class Heatmap : public Base
{
  public:
	void plot(const Display &display, const DataSet::Base &data, const Boundary &boundary, const ColorMap &colorMap) const override
	{

		Range<size_t> column_range{ 0, HEATMAP_COLUMNS };
		Range<size_t> row_range{ 0, HEATMAP_ROWS };
		Range<double> value_range{ static_cast<double>(data.length()), 0 };

		/* Auto range */
		if (HEATMAP_AUTORANGE)
		{
			for (size_t column = 0; column < HEATMAP_COLUMNS; ++column)
			{
				for (size_t row = 0; row < HEATMAP_ROWS; ++row)
				{
					CartesianVector<DataNorm> bl{ column_range.normalize(column), row_range.normalize(row) };
					CartesianVector<DataNorm> br{ column_range.normalize(column + 1), row_range.normalize(row) };
					CartesianVector<DataNorm> tl{ column_range.normalize(column), row_range.normalize(row + 1) };
					CartesianVector<DataNorm> tr{ column_range.normalize(column + 1), row_range.normalize(row + 1) };

					double cell_value = 0;
					for (auto it = data.begin(); it != data.end(); it++)
					{
						auto dataPoint = *it;
						double dx = pow(dataPoint.x() - bl.x(), 2);
						double dy = pow(dataPoint.y() - bl.y(), 2);
						double distance = sqrt(dx + dy);
						merge_distance(cell_value, distance);
					}
					value_range.update(cell_value);
				}
			}
		}
		else
		{
			value_range = { 0.0, 1.0 };
		}

		for (size_t column = 0; column < HEATMAP_COLUMNS; ++column)
		{
			for (size_t row = 0; row < HEATMAP_ROWS; ++row)
			{
				CartesianVector<DataNorm> bl{ column_range.normalize(column), row_range.normalize(row) };
				CartesianVector<DataNorm> br{ column_range.normalize(column + 1), row_range.normalize(row) };
				CartesianVector<DataNorm> tl{ column_range.normalize(column), row_range.normalize(row + 1) };
				CartesianVector<DataNorm> tr{ column_range.normalize(column + 1), row_range.normalize(row + 1) };

				double cell_value = 0;
				for (auto it = data.begin(); it != data.end(); it++)
				{
					auto dataPoint = *it;
					double dx = pow(dataPoint.x() - bl.x(), 2);
					double dy = pow(dataPoint.y() - bl.y(), 2);
					double distance = sqrt(dx + dy);
					merge_distance(cell_value, distance);
				}
				draw_block(display, boundary, colorMap, bl, br, tl, tr, value_range.normalize(cell_value));
			}
		}
	}

  protected:
	virtual void merge_distance(double &cell_value, double distance) const
	{
		cell_value = graficiMax(cell_value, 0.5 / (distance + 0.5));
	}
	virtual void draw_block(const Display &display, const Boundary &boundary, const ColorMap &colorMap, CartesianVector<DataNorm> bl, CartesianVector<DataNorm> br, CartesianVector<DataNorm> tl, CartesianVector<DataNorm> tr, DataNorm c) const
	{
		display.fillRect(boundary.project(bl),
		                 boundary.project(br),
		                 boundary.project(tl),
		                 boundary.project(tr),
		                 colorMap.project(c));
	}
};

} // namespace Plotter
#endif //GRAFICI_GFX_PLOTTER_HEATMAP_H
