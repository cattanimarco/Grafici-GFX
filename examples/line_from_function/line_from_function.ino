#include "Adafruit_GFX.h" // Hardware-specific library
#include "Adafruit_ILI9341.h"

#include "Grafici.h"

/* Setup display driver */
Adafruit_ILI9341 gfx = Adafruit_ILI9341(10, 9);

/* `data_x` = [0 .. 99] */
DataLinear data_x{ 100 };

/* `data_y` = [sin(0) ..  sin(PI * 99 * 0.05)] */
DataFunction data_y{ 100, [](size_t idx) -> float { return sin(M_PI * idx * 0.05); } };

void setup(void)
{
	/* Init display driver and select landscape mode */
	gfx.begin();
	gfx.setRotation(1);

	/* Init the plotting library with the display driver */
	Grafici plot{ gfx };

	/* Set the color map */
	plot.set_color_map(parula);

	/* Plot data as a line. Color line using `data_y` */
	plot.line(data_x, data_y, data_y);
}

void loop(void)
{
}
