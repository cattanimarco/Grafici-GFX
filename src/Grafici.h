/*!
* \file Grafici.h
* \author Marco Cattani <m.cattani@icloud.com>
* \version 3.0
* \date 26/02/2022
* \brief 
* \remarks None
* 
* 
* 
*/

/** \addtogroup Main
 *  @{
 */

#ifndef GRAFICI_GRAFICI_H
#define GRAFICI_GRAFICI_H

/*! Importation of librairies*/
#include "Range.h"
#include "data/DataNorm.h"

#include "data/DataArray.h"
#include "data/DataArrayXY.h"
#include "data/DataConstant.h"
#include "data/DataFunction.h"
#include "data/DataHistogramXY.h"
#include "data/DataInterpolatorL.h"
#include "data/DataLinear.h"
#include "data/DataResize.h"
#include "data/DataSourceNorm.h"
#include "data/DataSpline.h"

#include "color/ColorDefinitions.h"
#include "color/ColorMap.h"
#include "color/Color.h"

#include "display/DisplayDriver.h"
#include "display/DisplayVector.h"
#include "display/PolarWindow.h"
#include "display/Window.h"

#include "plotter/PlotAxis.h"
#include "plotter/PlotBar.h"
#include "plotter/PlotLine.h"
#include "plotter/PlotScatter.h"

/**
 * @brief Object representing the Grafici plotting library
 *
 */
class Grafici
{
  public:
	/**
	 * @brief Construct a new Grafici object
	 *
	 * @param hal reference to the Adafruit_GFX display driver
	 */
	Grafici(Adafruit_GFX &hal)
	    : _display_driver{ hal }
	{
		_display_driver.fill_rect({ 0, 0 }, { 1, 1 }, black);
	}

	/**
	 * @brief Set the default color map for plotting
	 *
	 * @param c reference to the color map
	 */
	void set_color_map(const ColorMap &c)
	{
		_color_map = &c;
	}

	/**
	 * @brief Set the properties for the plot axis. If this funtion is not called, 
	 * the default options are used, i.e. rows=0, columns=0, and style=none.
	 *
	 * @param opts axis properties
	 */
	void set_axis(PlotAxisOpts opts)
	{
		_axis_opts = opts;
	}

	/**
	 * @brief Plot a line on the display
	 * 
	 * @param x Data source for the x axis
	 * @param y Data source for the y axis
	 * @param c Data source for the color of the line  segments. Note that the final color is a function of the color map set via @ref set_color_map and the value from c
	 * @param window Optional drawing region used to draw the line. Default is fullscreen
	 * @param opts Optional line drawing options. There are no options available at the moment.
	 */
	void line(const DataSourceNorm &x,
	          const DataSourceNorm &y,
	          const DataSourceNorm &c,
	          const Window &window = full_screen,
	          const PlotLineOpts opts = {})
	{
		if (opts.draw_background)
		{
			_display_driver.fill_rect({ 0, 0 }, { 1, 1 }, opts.background_color, window, opts.segments);
		}
		plot_axis(_display_driver, window, _axis_opts);
		plot_line(_display_driver, window, *_color_map, x, y, c, opts);
	}

	/**
	 * @brief Plot a set of bars on the display
	 * 
	 * @param x Data source for the x axis
	 * @param y Data source for the y axis
	 * @param c Data source for the color of the bars. Note that the final color is a function of the color map set via @ref set_color_map and the value from c
	 * @param window Optional drawing region used to draw the line. Default is fullscreen
	 * @param opts Optional line drawing options. Default is thickness=0.8 and fill_bars=false.
	 */
	void bar(const DataSourceNorm &x,
	         const DataSourceNorm &y,
	         const DataSourceNorm &c,
	         const Window &window = full_screen,
	         const PlotBarOpts opts = {})
	{
		if (opts.draw_background)
		{
			_display_driver.fill_rect({ 0, 0 }, { 1, 1 }, opts.background_color, window, opts.segments);
		}
		plot_axis(_display_driver, window, _axis_opts);
		plot_bar(_display_driver, window, *_color_map, x, y, c, opts);
	}

	/**
	 * @brief Plot a set of markers on the display
	 * 
	 * @param x Data source for the x axis
	 * @param y Data source for the y axis
	 * @param c Data source for the color of the markers. Note that the final color is a function of the color map set via @ref set_color_map and the value from c
	 * @param s Data source for the size of the markers. The size is normalized. Hence a size of 1.0 will draw a marker as big as the display.
	 * @param window Optional drawing region used to draw the line. Default is fullscreen
	 * @param opts Optional scatter option. Default is the string "o", which will draw the marker as a circle. Multiple character can be used to create composite markers, e.g. "xo". All the possible marker shapes are "eps>^*x+o."
	 */
	void scatter(const DataSourceNorm &x,
	             const DataSourceNorm &y,
	             const DataSourceNorm &c,
	             const DataSourceNorm &s,
	             const Window &window = full_screen,
	             const PlotScatterOpts opts = {})
	{
		plot_axis(_display_driver, window, _axis_opts);
		plot_scatter(_display_driver, window, *_color_map, x, y, c, s, opts);
	}

  private:
	const DisplayDriver _display_driver;
	const ColorMap *_color_map{ &parula };
	PlotAxisOpts _axis_opts{ 0, 0, none, white, 1 };
};

#endif // GRAFICI_GRAFICI_H

/** @}*/