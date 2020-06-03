#include "Adafruit_GFX.h" // Hardware-specific library
#include "Adafruit_ILI9341.h"

#include "Grafici.h"

Adafruit_ILI9341 tft = Adafruit_ILI9341(10, 9);

constexpr size_t source_data_size = 9;
constexpr size_t spline_size = 97;
float array[source_data_size] = { 0, 2, 0, 1.5, 0, 0.5, 0, 1, 0 };

Linear x(source_data_size);
ArrayFloat y(array, source_data_size);
SplineInterpolator dataSpline{ x, y, y, y, spline_size };

void setup(void)
{
  tft.begin();
  tft.setRotation(1);

  grafici.begin(tft, Colors::csParula);
  grafici.clear();

	Boundary leftBoundary;
	leftBoundary.cropAbsoluteCartesian({ 0.02, 0.02 }, { 0.02, 0.02 }).cropGridCartesian(1, 2, 0, 0);
	grafici.plot(line, dataSpline, leftBoundary);

	PolarBoundary rightBoundary;
	rightBoundary.cropAbsoluteCartesian({ 0.02, 0.02 }, { 0.02, 0.02 }).cropGridCartesian(1, 2, 0, 1);
	grafici.plot(line, dataSpline, rightBoundary);
}

void loop(void)
{
}
