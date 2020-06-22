#ifndef GRAFICI_GRAFICI_H
#define GRAFICI_GRAFICI_H

#include "Adafruit_GFX.h"
#include "Boundary.h"
#include "Color.h"
#include "Color_defs.h"
#include "DataSet.h"
#include "Display.h"
#include "Plotter.h"
#include "Types.h"

#include "Plotter/Bar.h"
#include "Plotter/Line.h"
#include "Plotter/Scatter.h"
#include "Plotter/Heatmap.h"
#include "Plotter/Bubblemap.h"
#include "Plotter/Axis.h"

#include "DataSet/LinearInterpolator.h"
#include "DataSet/SplineInterpolator.h"

#include "DataSource/Array.h"
#include "DataSource/BarIndex.h"
#include "DataSource/Constant.h"
#include "DataSource/Histogram.h"
#include "DataSource/Linear.h"
#include "DataSource/Parametric.h"

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
extern Plotter::Axis axis;

/* ALIASES */
namespace DataSource
{
/* this is to hide templates to final users */
using ArrayFloat = Array<float>;
using ArrayInt = Array<int>;
} // namespace DataSource

using DataSet::SplineInterpolator;
using DataSet::LinearInterpolator;

using DataSource::Constant;
using DataSource::Linear;
using DataSource::BarIndex;
using DataSource::ArrayFloat;
using DataSource::ArrayInt;
using DataSource::Histogram;

/* MAIN CLASS */
class Grafici
{
  public:
	Grafici() = default;

	void begin(Adafruit_GFX &tft, const ColorMap &colorMap)
	{
		_display.begin(tft);
		_colorMap = &colorMap;
	}

	void plot(const Plotter::Base &plotter, const DataSet::Base &data, const Boundary &boundary = fullScreen) const
	{
		plotter.plot(_display, data, boundary, *_colorMap);
	}

	void plot(const Plotter::Base &plotter, const DataSource::Base<DataNorm> &x, const DataSource::Base<DataNorm> &y, const DataSource::Base<DataNorm> &c, const DataSource::Base<DataNorm> &opt, const Boundary &boundary = fullScreen) const
	{
		plot(plotter, { x, y, c, opt }, boundary);
	};

	void plot(const Plotter::Base &plotter, const DataSource::Base<DataNorm> &x, const DataSource::Base<DataNorm> &y, const DataSource::Base<DataNorm> &c, const Boundary &boundary = fullScreen) const
	{
		plot(plotter, { x, y, c, c }, boundary);
	};

	ColorVector &bkgColor()
	{
		return _bkgColor;
	}

	const ColorMap **colorMap()
	{
		return &_colorMap;
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
