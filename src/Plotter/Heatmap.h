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
				Range<DataNorm> x {static_cast<DataNorm>(column_range.normalize(column)),static_cast<DataNorm>(column_range.normalize(column+1))};
				Range<DataNorm> y {static_cast<DataNorm>(row_range.normalize(row)),static_cast<DataNorm>(row_range.normalize(row+1))};

				double cell_value = 0;
				for (auto it = data.begin(); it != data.end(); it++)
				{
					auto dataPoint = *it;
					double dx = pow(dataPoint.x() - x.mid(), 2);
					double dy = pow(dataPoint.y() - y.mid(), 2);
					double distance = sqrt(dx + dy);
					merge_distance(cell_value, distance);
				}

				draw_block(display, boundary, colorMap, x, y, value_range.normalize(cell_value));
			}
		}
	}

  protected:
	virtual void merge_distance(double &cell_value, double distance) const
	{
		cell_value = graficiMax(cell_value, 0.5 / (distance + 0.5));
	}

	virtual void draw_block(const Display &display,
	                        const Boundary &boundary,
	                        const ColorMap &colorMap,
	                        Range<DataNorm> x,
	                        Range<DataNorm> y,
	                        DataNorm c) const
	{
		display.fillRect(boundary.project({ x.low(), y.low() }),
		                 boundary.project({ x.high(), y.low() }),
		                 boundary.project({ x.low(), y.high() }),
		                 boundary.project({ x.high(), y.high() }),
		                 colorMap.project(c));
	}
};

} // namespace Plotter
#endif //GRAFICI_GFX_PLOTTER_HEATMAP_H
