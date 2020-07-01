#include "Adafruit_GFX.h" // Hardware-specific library
#include "Adafruit_ILI9341.h"

#include "Grafici.h"

Adafruit_ILI9341 tft = Adafruit_ILI9341(10, 9);

constexpr size_t source_data_size = 9;
constexpr size_t spline_size = 33;
float array[source_data_size] = { 0, 2, 0, 1.5, 0, 0.5, 0, 1, 0 };
Linear x(source_data_size);
ArrayFloat y(array, source_data_size);
Constant opt(source_data_size, 0.5);
SplineInterpolator dataSpline{ x, y, y, opt, spline_size };
Boundary leftBoundary;
PolarBoundary rightBoundary;

void setup(void)
{
	tft.begin();
	tft.setRotation(1);

	grafici.begin(tft);
	grafici.clear();

	leftBoundary.cropAbsoluteCartesian({ 0.02, 0.02 }, { 0.02, 0.02 });
	leftBoundary.cropGridCartesian(1, 2, 0, 0);
	grafici.colorMap(Colors::blackAndWhite);
	grafici.plot(axis, Linear(25), Linear(10), Constant(25, 0.1), leftBoundary);
	grafici.colorMap(Colors::heat);
	grafici.plot(bar, dataSpline, leftBoundary);

	rightBoundary.cropAbsoluteCartesian({ 0.02, 0.02 }, { 0.02, 0.02 });
	rightBoundary.cropGridCartesian(1, 2, 0, 1);
	grafici.colorMap(Colors::blackAndWhite);
	grafici.plot(axis, Linear(25), Linear(10), Constant(25, 0.1), rightBoundary);
	grafici.colorMap(Colors::heat);
	grafici.plot(bar, dataSpline, rightBoundary);
}

void loop(void)
{
}
