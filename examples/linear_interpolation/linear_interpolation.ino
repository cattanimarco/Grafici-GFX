#include "Adafruit_GFX.h" // Hardware-specific library
#include "Adafruit_ILI9341.h"

#include "Grafici.h"

Adafruit_ILI9341 gfx = Adafruit_ILI9341(10, 9);

constexpr size_t array_elements = 5;
constexpr size_t interpolated_elements = 100;

float array[array_elements] = { 1, 0, 2, 1, 2 };
DataSource::Linear x(array_elements);
DataSource::Array<float> y(array, array_elements);
DataSet::SplineInterpolator dataSpline{ x, y, y, y, interpolated_elements };

void setup(void)
{
	gfx.begin();
	gfx.setRotation(1);

	grafici.begin(gfx, Colors::rainbow);
	grafici.clear();
	grafici.plot(line, dataSpline);
}

void loop(void)
{
}
