#include "Adafruit_GFX.h" // Hardware-specific library
#include "Adafruit_ILI9341.h"

#include "Grafici.h"

Adafruit_ILI9341 tft = Adafruit_ILI9341(10, 9);

constexpr size_t num_elem = 5;
float array[num_elem] = { 1, 0, 2, 1, 2 };
Linear x(num_elem);
ArrayFloat y(array, num_elem);
SplineInterpolator dataSpline{ x, y, y, y, 85 };

void setup(void)
{
	tft.begin();
	tft.setRotation(1);
	grafici.begin(tft, Colors::rainbow);
	grafici.clear();

	grafici.plot(line, dataSpline);
}

void loop(void)
{
}
