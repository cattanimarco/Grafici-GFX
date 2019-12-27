#ifndef GRAFICI_GFX_PLOT_LINE_H
#define GRAFICI_GFX_PLOT_LINE_H

#include "../Plotter.h"

class LinePlot : public Plotter
{
  public:
	void plot(const DataSource &dataX, const DataSource &dataY, const DataSource &dataZ, const DataSource &dataColor) const override
	{

		//data iterators
		//arry of iterators
		auto itX = dataX.begin();
		auto itY = dataY.begin();
		auto itC = dataColor.begin();

		auto preX = *(itX);
		auto preX = *(itY);
		auto preX = *(itZ);

		while ((itX != dataX.end()) && (itY != dataY.end()) && (itC != dataColor.end()))
		{
			auto curX = *(++itX);
			auto curX = *(++itY);
			auto curX = *(++itZ);
		}

		for (DataCoordinates previous = *(++it); it != dataSource->end(); previous = *(++it))
		{
			DataCoordinates actual = *it;
			displayDriver->drawLine(boundaries->project(previous),
			                        boundaries->project(actual),
			                        theme->project(actual));
		}
	}
};

#endif //GRAFICI_GFX_PLOT_LINE_H