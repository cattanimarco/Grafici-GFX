#include "Adafruit_GFX.h" // Hardware-specific library
#include "Adafruit_ILI9341.h"

#include "Grafici.h"

/* Setup display driver */
Adafruit_ILI9341 gfx = Adafruit_ILI9341(10, 9);

constexpr size_t ARRAY_SIZE = 10;
constexpr size_t SPLINE_SIZE = 50;
constexpr size_t MAX_VALUE = 255;

unsigned int raw_data[ARRAY_SIZE];

void setup(void)
{
	/* Init display driver and select landscape mode */
	gfx.begin();
	gfx.setRotation(1);

	/* Init the plotting library with the display driver */
	Grafici plot{ gfx };

	DataArrayXY<unsigned int> data{ raw_data, ARRAY_SIZE, { 0, MAX_VALUE } };

	/* generate some random data and save it into `raw_data` */
	randomSeed(66);
	for (size_t i = 0; i < ARRAY_SIZE; ++i)
	{
		raw_data[i] = random(MAX_VALUE + 1);
	}

	/* Set the color map */
	plot.set_color_map(parula);

	/* Interpolate the data in `raw_data` (from 10 to 50 points) */
	DataSpline<SPLINE_SIZE> data_interpolated{data.x(),data.y()};

	/* Plot data as a line. Color line using `data_y` */
	plot.line(data_interpolated.x(), data_interpolated.y(), data_interpolated.y(), full_screen);
}

void loop(void)
{
}