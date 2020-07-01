#include "Adafruit_GFX.h" // Hardware-specific library
#include "Adafruit_ILI9341.h"

#include "Grafici.h"

Adafruit_ILI9341 tft = Adafruit_ILI9341(10, 9);

constexpr size_t num_elem = 5;
float array_y1[num_elem] = { 1, 2, 3, 4, 5 };
float array_y2[num_elem] = { 2, 3, 4, 5, 6 };
float array_x1[num_elem] = { 2, 3, 4, 5, 6 };
float array_x2[num_elem] = { 0, 1, 2, 3, 4 };
Linear xAxis(7);
Linear yAxis(6, -1, 1);
ArrayFloat y1(array_y1, num_elem);
ArrayFloat y2(array_y2, num_elem);
ArrayFloat x1(array_x1, num_elem);
ArrayFloat x2(array_x2, num_elem);

void setup(void)
{
	tft.begin();
	tft.setRotation(1);

	grafici.begin(tft);
	grafici.clear();

	/* set each limit as the union (using + sign) of all the limits*/
	x1.limits() = x2.limits() = xAxis.limits() = (x1.limits() + x2.limits() + xAxis.limits());
	y1.limits() = y2.limits() = yAxis.limits() = (y1.limits() + y2.limits() + yAxis.limits());

	grafici.colorMap(Colors::blackAndWhite);
	grafici.plot(axis, xAxis, yAxis, Constant(8, 0.1));
	grafici.colorMap(Colors::semaphore);
	grafici.plot(line, x1, y1, y1);
	grafici.plot(line, x2, y2, y2);
}

void loop(void)
{
}
