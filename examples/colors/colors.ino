#include "Adafruit_GFX.h" // Hardware-specific library
#include "Adafruit_ILI9341.h"

#include "Grafici.h"

Adafruit_ILI9341 tft = Adafruit_ILI9341(10, 9);

constexpr size_t data_size = 240;
const ColorMap *colorPlots[] = { &Colors::rainbow,
	                             &Colors::temperature,
	                             &Colors::blackAndWhite,
	                             &Colors::cmy,
	                             &Colors::heat,
	                             &Colors::bright,
	                             &Colors::semaphore,
	                             &Colors::parula };
Linear x(data_size);
Constant y(data_size, 1.0);
Constant opt(data_size, 1.0);

void setup(void)
{
	tft.begin();
	tft.setRotation(1);

	grafici.begin(tft);
	grafici.clear();

	for (size_t idx = 0; idx < sizeof(colorPlots) / sizeof(ColorMap *); idx++)
	{
		Boundary boundary;
		grafici.colorMap(*colorPlots[idx]);
		boundary.cropGridCartesian(8, 1, idx).cropAbsoluteCartesian({ 0.01, 0.01 }, { 0.01, 0.01 });
		grafici.plot(bar, x, y, x, opt, boundary);
	}
}

void loop(void)
{
}
