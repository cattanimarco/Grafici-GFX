#include "Adafruit_GFX.h" // Hardware-specific library
#include "Adafruit_ILI9341.h"

#include "Grafici.h"

Adafruit_ILI9341 tft = Adafruit_ILI9341(10, 9);

constexpr size_t array_elements = 5;
// Chose a big enough number for the samples. Too small and you risk sub-sampling issues
// Even better chose samples = n + (n-1) * x (in this example x = 20)
constexpr size_t interpolated_elements = 85;

float dataArray[array_elements] = { 1, 0, 2, 1, 2 };
float colorArray[array_elements] = { 0, 1, 2, 3, 4 };
Linear x(array_elements);
ArrayFloat y(dataArray, array_elements);
ArrayFloat c(colorArray, array_elements);
LinearInterpolator dataLinear{ x, y, c, c, interpolated_elements };

void setup(void)
{
  tft.begin();
  tft.setRotation(1);

  grafici.begin(tft, Colors::heat);
  grafici.clear();

  grafici.plot(line, dataLinear);
}

void loop(void)
{
}
