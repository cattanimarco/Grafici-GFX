#ifndef GRAFICI_GRAFICI_H
#define GRAFICI_GRAFICI_H

#ifndef MAP_COLUMNS
#define MAP_COLUMNS 32
#endif

#ifndef MAP_ROWS
#define MAP_ROWS 24
#endif

#ifndef HEATMAP_AUTORANGE
#define HEATMAP_AUTORANGE true
#endif

#ifndef CELLMAP_TRESHOLD
#define CELLMAP_TRESHOLD 0.1
#endif

#ifndef SPLINE_AUTOSCALE
#define SPLINE_AUTOSCALE true
#endif

#include "Adafruit_GFX.h"
#include "Boundary.h"
#include "Color.h"
#include "Color_defs.h"
#include "DataSet.h"
#include "Display.h"
#include "Plotter.h"
#include "Types.h"

#include "Plotter/Axis.h"
#include "Plotter/Bar.h"
#include "Plotter/Bubblemap.h"
#include "Plotter/Cellmap.h"
#include "Plotter/Cliquegraph.h"
#include "Plotter/Heatmap.h"
#include "Plotter/Line.h"
#include "Plotter/Scatter.h"

#include "DataSets/LinearInterpolator.h"
#include "DataSets/SplineInterpolator.h"

#include "DataSources/Array.h"
#include "DataSources/BarIndex.h"
#include "DataSources/Constant.h"
#include "DataSources/Histogram.h"
#include "DataSources/Linear.h"
#include "DataSources/Parametric.h"

/* Instance of a Grafici object. Used instead of a singleton patter as it is simpler 
to use this way for arduino users and there can be multiple instances of this object if it is relly needed */

/* GLOBAL VARS */
class Grafici;
extern Grafici grafici;
extern Boundary fullScreen;
extern Plotter::Line line;
extern Plotter::Bar bar;
extern Plotter::Scatter scatter;
extern Plotter::Heatmap heatmap;
extern Plotter::Bubblemap bubblemap;
extern Plotter::Cellmap cellmap;
extern Plotter::Cliquegraph cliquegraph;
extern Plotter::Axis axis;

/* ALIASES */
namespace DataSources
{
/* this is to hide templates to final users */
using ArrayFloat = Array<float>;
using ArrayInt = Array<int>;
} // namespace DataSources

using DataSets::LinearInterpolator;
using DataSets::SplineInterpolator;

using DataSources::ArrayFloat;
using DataSources::ArrayInt;
using DataSources::BarIndex;
using DataSources::Constant;
using DataSources::Histogram;
using DataSources::Linear;

/* MAIN CLASS */
class Grafici
{
  public:
	Grafici() = default;

	void begin(Adafruit_GFX &tft, const ColorMap &colorMap = Colors::blackAndWhite)
	{
		_display.begin(tft);
		_colorMap = &colorMap;
	}

	void plot(const Plotter::Base &plotter, const DataSets::DataSet &data, const Boundary &boundary = fullScreen) const
	{
		plotter.plot(_display, data, boundary, *_colorMap);
	}

	void plot(const Plotter::Base &plotter, const DataSources::DataSource<DataNorm> &x, const DataSources::DataSource<DataNorm> &y, const DataSources::DataSource<DataNorm> &c, const DataSources::DataSource<DataNorm> &opt, const Boundary &boundary = fullScreen) const
	{
		plot(plotter, { x, y, c, opt }, boundary);
	};

	void plot(const Plotter::Base &plotter, const DataSources::DataSource<DataNorm> &x, const DataSources::DataSource<DataNorm> &y, const DataSources::DataSource<DataNorm> &c, const Boundary &boundary = fullScreen) const
	{
		plot(plotter, { x, y, c, c }, boundary);
	};

	ColorVector &bkgColor()
	{
		return _bkgColor;
	}

	void colorMap(const ColorMap &colorMap)
	{
		_colorMap = &colorMap;
	}

	void clear()
	{
		_display.driver().fillScreen(_bkgColor.toColorGFX());
	}

	void clear(Boundary &boundary)
	{
		auto bl = boundary.project({ 0.0, 0.0 });
		auto tr = boundary.project({ 1.0, 1.0 });
		_display.fillRect(bl, tr, _bkgColor.toColorGFX());
	}

  private:
	Display _display;
	const ColorMap *_colorMap;
	ColorVector _bkgColor{ Colors::black };
};

#endif //GRAFICI_GRAFICI_H
