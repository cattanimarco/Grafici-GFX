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
DataSource::BarIndex histogramX(histogram_size);
DataSource::Constant dataOpt1(histogram_size, 0.5);
DataSet::SplineInterpolator dataSpline{ x, y, y, y, spline_size };
DataSource::Histogram dataHistogram{ dataSpline.y(), histogram_size };
DataSource::Constant barY(spline_size, 1.0);
DataSource::Constant dataOpt2(spline_size, 0.0);

Boundary leftBoundary;
Boundary rightTopBoundary;
Boundary rightBottomBoundary;


void setup(void)
{
  tft.begin();
  tft.setRotation(1);

  grafici.begin(tft, Colors::csParula);
  grafici.clear();

  leftBoundary.cropGridCartesian(1, 2, 0, 0).cropAbsoluteCartesian({ 0.04, 0.02 }, { 0.04, 0.04 });
  rightTopBoundary.cropGridCartesian(2, 2, 0, 1).cropAbsoluteCartesian({ 0.02, 0.04 }, { 0.04, 0.02 });
  rightBottomBoundary.cropGridCartesian(2, 2, 1, 1).cropAbsoluteCartesian({ 0.02, 0.04 }, { 0.02, 0.04 });

  grafici.plot(line, dataSpline, leftBoundary);
  grafici.plot(bar, histogramX, dataHistogram, histogramX, dataOpt1, rightTopBoundary);
  DataSource::Select splineY = dataSpline.y();
  grafici.plot(bar, splineY, barY, splineY, dataOpt2, rightBottomBoundary);


}

void loop(void)
{
}
