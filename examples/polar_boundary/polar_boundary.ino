#include "Adafruit_GFX.h" // Hardware-specific library
#include "Adafruit_ILI9341.h"

#include "Grafici.h"

Adafruit_ILI9341 tft = Adafruit_ILI9341(10, 9);

constexpr size_t source_data_size = 9;
constexpr size_t spline_size = 49;
float array[source_data_size] = { 0, 2, 0, 2, 0, 1, 0, 1, 0 };
Linear x(source_data_size);
ArrayFloat y(array, source_data_size);
Constant opt(source_data_size, 0.0);
SplineInterpolator dataSpline{ x, y, y, opt, spline_size };
PolarBoundary leftBoundary;
PolarBoundary rightBoundary;
PolarBoundary rightBottomBoundary;
PolarBoundary middleBottomBoundary;
PolarBoundary rightTopBoundary;

void setup(void)
{
	tft.begin();
	tft.setRotation(1);

	grafici.begin(tft, Colors::parula);
	grafici.clear();

	leftBoundary.cropGridCartesian(1, 2, 0, 0);
	leftBoundary.cropAbsoluteCartesian({ 0.02, 0.02 }, { 0.02, 0.02 });
	leftBoundary.cropGridPolar(1, 2, 0, 0);
	grafici.colorMap(Colors::blackAndWhite);
	grafici.plot(axis, Linear(19), Linear(5), Constant(10, 0), leftBoundary);
	grafici.colorMap(Colors::parula);
	grafici.plot(bar, dataSpline, leftBoundary);

	rightBoundary.cropGridCartesian(1, 2, 0, 1);
	rightBoundary.cropAbsoluteCartesian({ 0.02, 0.02 }, { 0.02, 0.02 });
	rightBoundary.cropRelativePolar({ 0, 0.25 }, { 0, 0.0 });
	grafici.colorMap(Colors::blackAndWhite);
	grafici.plot(axis, Linear(28), Linear(5), Constant(10, 0), rightBoundary);
	grafici.colorMap(Colors::parula);

	rightBottomBoundary.cropAbsoluteCartesian({ 0.02, 0.02 }, { 0.02, 0.02 });
	rightBottomBoundary.cropGridCartesian(1, 2, 0, 1);
	rightBottomBoundary.cropRelativePolar({ 0, 0.25 }, { 0, 0.5 });
	grafici.plot(bar, dataSpline, rightBottomBoundary);

	middleBottomBoundary.cropAbsoluteCartesian({ 0.02, 0.02 }, { 0.02, 0.02 });
	middleBottomBoundary.cropGridCartesian(1, 2, 0, 1);
	middleBottomBoundary.cropRelativePolar({ 0, 0.25 }, { 0.35, 0.35 });
	grafici.plot(scatter, dataSpline.x(), dataSpline.y(), dataSpline.c(), Constant(spline_size, 0.01), middleBottomBoundary);

	rightTopBoundary.cropAbsoluteCartesian({ 0.02, 0.02 }, { 0.02, 0.02 });
	rightTopBoundary.cropGridCartesian(1, 2, 0, 1);
	rightTopBoundary.cropRelativePolar({ 0, 0.25 }, { 0.5, 0.0 });
	grafici.plot(line, dataSpline, rightTopBoundary);
}

void loop(void)
{
}
