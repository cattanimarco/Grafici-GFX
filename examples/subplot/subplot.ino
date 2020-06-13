#include "Adafruit_GFX.h" // Hardware-specific library
#include "Adafruit_ILI9341.h"

#include "Grafici.h"

Adafruit_ILI9341 tft = Adafruit_ILI9341(10, 9);

constexpr size_t source_data_size = 6;
constexpr size_t spline_size = 56;
constexpr size_t histogram_size = 10;
float array[source_data_size] = { 1, 0, 2, 1, 2, 2 };

Linear x(source_data_size);
ArrayFloat y(array, source_data_size);
SplineInterpolator dataSpline{ x, y, y, y, spline_size };
Histogram dataHistogram{ dataSpline.y(), histogram_size };

Boundary leftBoundary;
Boundary rightTopBoundary;
Boundary rightBottomBoundary;


void setup(void)
{
  tft.begin();
  tft.setRotation(1);

  grafici.begin(tft, Colors::parula);
  grafici.clear();

  leftBoundary.cropGridCartesian(1, 2, 0, 0);
  leftBoundary.cropAbsoluteCartesian({ 0.04, 0.02 }, { 0.04, 0.04 });
  rightTopBoundary.cropGridCartesian(2, 2, 0, 1);
  rightTopBoundary.cropAbsoluteCartesian({ 0.02, 0.04 }, { 0.04, 0.02 });
  rightBottomBoundary.cropGridCartesian(2, 2, 1, 1);
  rightBottomBoundary.cropAbsoluteCartesian({ 0.02, 0.04 }, { 0.02, 0.04 });

  grafici.plot(line, dataSpline, leftBoundary);
  grafici.plot(bar, BarIndex(histogram_size), dataHistogram, BarIndex(histogram_size), Constant(histogram_size, 0.5), rightTopBoundary);
  grafici.plot(bar, dataSpline.y(), Constant(spline_size, 1.0), dataSpline.y(), Constant(spline_size, 0.0), rightBottomBoundary);
}

void loop(void)
{
}
