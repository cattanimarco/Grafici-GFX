#include "Adafruit_GFX.h" // Hardware-specific library
#include "Adafruit_ILI9341.h"

#include "Grafici.h"

Adafruit_ILI9341 tft = Adafruit_ILI9341(10, 9);

constexpr size_t source_data_size = 6;
constexpr size_t spline_size = 86;
constexpr size_t histogram_size = 20;
float array[source_data_size] = { 1, 0, 2, 1, 2, 2 };
Linear x(source_data_size);
ArrayFloat y(array, source_data_size);
SplineInterpolator dataSpline{ x, y, y, y, spline_size };
Histogram dataHistogram{ dataSpline.y(), histogram_size };
Boundary barBoundary;
Boundary lineBoundary;

void setup(void)
{
	tft.begin();
	tft.setRotation(1);

	grafici.begin(tft, Colors::temperature);
	grafici.clear();

	barBoundary.cropRelativeCartesian({ 0.04, 0.04 }, { 0.04, 0.04 }).boundaryRotation() = BoundaryRotation::clockWise90;
	lineBoundary.cropRelativeCartesian({ 0.04, 0.04 }, { 0.04, 0.04 });
	grafici.plot(bar, BarIndex(histogram_size), dataHistogram, BarIndex(histogram_size), Constant(histogram_size, 0.0), barBoundary);
	grafici.plot(line, dataSpline, lineBoundary);
	grafici.plot(scatter, dataSpline.x(), dataSpline.y(), dataSpline.y(), Constant(spline_size, 0.015), lineBoundary);
}

void loop(void)
{
}
