#include "Adafruit_GFX.h" // Hardware-specific library
#include "Adafruit_ILI9341.h"

#include "Grafici.h"

Adafruit_ILI9341 tft = Adafruit_ILI9341(10, 9);

constexpr size_t source_data_size = 6;
constexpr size_t spline_size = 56;
constexpr size_t histogram_size = 20;
float array[source_data_size] = { 1, 0, 2, 1, 2, 2 };

DataSource::Linear x(source_data_size);
DataSource::Array<float> y(array, source_data_size);
DataSet::SplineInterpolator dataSpline{ x, y, y, y, spline_size };
DataSource::Histogram dataHistogram{ dataSpline.y(), histogram_size };

Boundary barBoundary;
Boundary lineBoundary;

void setup(void)
{
  tft.begin();
  tft.setRotation(1);

  grafici.begin(tft, Colors::temperature);
  grafici.clear();

  barBoundary.cropRelativeCartesian({ 0.04, 0.04 }, { 0.04, 0.04 });
  barBoundary.boundaryRotation() = BoundaryRotation::clockWise90;
  lineBoundary.cropRelativeCartesian({ 0.04, 0.04 }, { 0.04, 0.04 });

  grafici.plot(bar, DataSource::BarIndex(histogram_size), dataHistogram, DataSource::BarIndex(histogram_size), DataSource::Constant(histogram_size, 0.0), barBoundary);
  grafici.plot(line, dataSpline, lineBoundary);
}

void loop(void)
{
}
