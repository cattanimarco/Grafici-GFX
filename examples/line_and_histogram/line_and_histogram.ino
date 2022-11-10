#include "Adafruit_GFX.h" // Hardware-specific library
#include "Adafruit_ILI9341.h"

#include "Grafici.h"

/* setup display driver */
Adafruit_ILI9341 gfx = Adafruit_ILI9341(10, 9);

/* constants */
constexpr size_t ARRAY_SIZE = 120;
constexpr size_t HISTOGRAM_BINS = 20;
float raw_data[ARRAY_SIZE];

void setup(void)
{
	/* init display driver and select landscape mode */
	gfx.begin();
	gfx.setRotation(1);

	/* init the plotting library with the display driver */
	Grafici plot{ gfx };

	/* set the color map */
	plot.set_color_map(cmy);


	/* == LEFT PLOT == */

	/* define a screen region between 0% and 74% of the total width and between 0% and 100% of the total height */
	auto left_window = full_screen.sub_window({ 0, .74 }, { 0, 1 });

	/* enable horizontal sub axis in gray */
	plot.set_axis({ HISTOGRAM_BINS, 1, h_lines, white * 0.5 });

	/* generate some random data and save it into `raw_data` */
	randomSeed(66);
	for (size_t i = 0; i < ARRAY_SIZE; ++i)
	{
		/* approximate normal distribution using Box-Muller transform */
		raw_data[i] = sqrt(-2 * log((random(HISTOGRAM_BINS) + 1) / (float)HISTOGRAM_BINS)) * sin(M_PI * 2.0 * random(HISTOGRAM_BINS) / (float)HISTOGRAM_BINS);
	}

	/* x and y data sources */
	DataArrayXY<float> data{ raw_data, ARRAY_SIZE };

	/* break plot lines in multiple segments to create a gradient of colors between two data points */
	PlotLineOpts left_opts;
	left_opts.segments = 10;

	/* plot x and y data using lines. Color the lines using y and according to `left_opts` */
	plot.line(data.x(), data.y(), data.y(), left_window, left_opts);


	/* == RIGHT PLOT == */

	/* define a screen region between 76% and 100% of the total width and between 0% and 100% of the total height */
	auto right_window = full_screen.sub_window({ .76, 1 }, { 0, 1 }).transform(WindowTransform::ccw_90_rotation);

	/* enable horizontal and vertical sub axis in gray */
	plot.set_axis({ 5, HISTOGRAM_BINS, h_lines | v_lines, white * 0.5 });

	/* create a new data source by counting the frequencies of y data */
	DataHistogramXY<HISTOGRAM_BINS> data_hist{ data.y() };

	/* bars are filled and use 50% of the their width */
	PlotBarOpts right_opts;
	right_opts.fill_bars = true;
	right_opts.thickness = 0.5;

	/* plot histogram data using bars. Color the bars using y and according to `right_opts` */
	plot.bar(data_hist.x(), data_hist.y(), data_hist.x(), right_window, right_opts);
}

void loop(void)
{
}