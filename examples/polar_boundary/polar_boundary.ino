#include "Adafruit_GFX.h" // Hardware-specific library
#include "Adafruit_ILI9341.h"

#include "Grafici.h"

Adafruit_ILI9341 tft = Adafruit_ILI9341(10, 9);

constexpr size_t source_data_size = 9;
constexpr size_t spline_size = 97;
float array[source_data_size] = { 0, 2, 0, 2, 0, 1, 0, 1, 0 };

Linear x(source_data_size);
ArrayFloat y(array, source_data_size);
Constant opt(source_data_size, 0.0);
SplineInterpolator dataSpline{ x, y, y, opt, spline_size };

void setup(void)
{
  tft.begin();
  tft.setRotation(1);

  grafici.begin(tft, Colors::parula);
  grafici.clear();

  PolarBoundary leftBoundary;
  leftBoundary.cropAbsoluteCartesian({ 0.02, 0.02 }, { 0.02, 0.02 });
  leftBoundary.cropGridCartesian(1, 2, 0, 0);
  leftBoundary.cropGridPolar(1, 2, 0, 0);
  grafici.plot(bar, dataSpline, leftBoundary);
  
  PolarBoundary rightBottomBoundary;
  rightBottomBoundary.cropAbsoluteCartesian({ 0.02, 0.02 }, { 0.02, 0.02 });
  rightBottomBoundary.cropGridCartesian(1, 2, 0, 1);
  rightBottomBoundary.cropRelativePolar({ 0, 0.25 }, { 0, 0.5 });
  grafici.plot(bar, dataSpline, rightBottomBoundary);
  
  // PolarBoundary middleBottomBoundary;
  // middleBottomBoundary.cropAbsoluteCartesian({ 0.02, 0.02 }, { 0.02, 0.02 });
  // middleBottomBoundary.cropGridCartesian(1, 2, 0, 1);
  // middleBottomBoundary.cropRelativePolar({ 0, 0.25 }, { 0.35, 0.35 });
  // grafici.plot(scatter, dataSpline, middleBottomBoundary);
  
  PolarBoundary rightTopBoundary;
  rightTopBoundary.cropAbsoluteCartesian({ 0.02, 0.02 }, { 0.02, 0.02 });
  rightTopBoundary.cropGridCartesian(1, 2, 0, 1);
  rightTopBoundary.cropRelativePolar({ 0, 0.25 }, { 0.5, 0.0 });
  grafici.plot(line, dataSpline, rightTopBoundary);
}

void loop(void)
{
}
