#include "Adafruit_GFX.h" // Hardware-specific library
#include "Adafruit_ILI9341.h"

#include "Grafici.h"

Adafruit_ILI9341 tft = Adafruit_ILI9341(10, 9);

constexpr size_t num_elem = 6;
float arrayX[num_elem] = { 0, 1, 2, 2, 3, 4 };
float arrayY[num_elem] = { 1, 0, 2, 1, 1, 2 };
ArrayFloat x(arrayX, num_elem);
ArrayFloat y(arrayY, num_elem);
Constant opt(num_elem, 0.02);
Constant c(num_elem, 0);
Boundary bl;
Boundary br;
Boundary tl;
Boundary tr;

void setup(void)
{
	tft.begin();
	tft.setRotation(1);

	grafici.begin(tft, Colors::parula);
	grafici.clear();

	bl.cropGridCartesian(2, 2, 0, 0);
	bl.cropAbsoluteCartesian({ 0.01, 0.01 }, { 0.01, 0.01 });
	grafici.plot(heatmap, x, y, c, opt, bl);
	grafici.plot(scatter, x, y, c, opt, bl);

	br.cropGridCartesian(2, 2, 0, 1);
	br.cropAbsoluteCartesian({ 0.01, 0.01 }, { 0.01, 0.01 });
	grafici.plot(bubblemap, x, y, c, opt, br);
	grafici.plot(scatter, x, y, c, opt, br);

	tl.cropGridCartesian(2, 2, 1, 0);
	tl.cropAbsoluteCartesian({ 0.01, 0.01 }, { 0.01, 0.01 });
	grafici.plot(cellmap, x, y, x, opt, tl);
	grafici.plot(scatter, x, y, c, opt, tl);

	tr.cropGridCartesian(2, 2, 1, 1);
	tr.cropAbsoluteCartesian({ 0.01, 0.01 }, { 0.01, 0.01 });
	grafici.plot(cliquegraph, x, y, x, opt, tr);
	grafici.plot(scatter, x, y, c, opt, tr);
}

void loop(void)
{
}
