#include "Adafruit_GFX.h" // Hardware-specific library
#include "Adafruit_ILI9341.h"

#include "Grafici.h"

Adafruit_ILI9341 tft = Adafruit_ILI9341(10, 9);

constexpr size_t array_elements = 5;
constexpr size_t interpolated_elements = 50;

float dataArray[array_elements] = { 1, 0, 2, 1, 2 };
float colorArray[array_elements] = { 0, 1, 2, 3, 4 };
DataSource::Linear x(array_elements);
DataSource::Array<float> y(dataArray, array_elements);
DataSource::Array<float> c(colorArray, array_elements);
DataSet::SplineInterpolator dataSpline{ x, y, c, c, interpolated_elements };

void setup(void)
{
	tft.begin();
	tft.setRotation(1);

	grafici.begin(tft, Colors::csHeat);
	grafici.clear();
	grafici.plot(line, dataSpline);
}

void loop(void)
{
}
