#include "Adafruit_GFX.h" // Hardware-specific library
#include "Adafruit_ILI9341.h"

#include "Grafici.h"

Adafruit_ILI9341 tft = Adafruit_ILI9341(10, 9);

constexpr size_t num_elem = 5;
float dataArray[num_elem] = { 1, 0, 2, 1, 2 };
DataSource::Array<float> y(dataArray, num_elem);

void setup(void)
{
  tft.begin();
  tft.setRotation(1);

  grafici.begin(tft, Colors::blackAndWhite);
  grafici.clear();
  grafici.plot(line, DataSource::Linear(num_elem), y, DataSource::Constant(num_elem, 1.0));
}

void loop(void)
{
}
