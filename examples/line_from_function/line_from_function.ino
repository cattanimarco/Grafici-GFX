#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"  // display-specific library
#include "Grafici.h"

Adafruit_ILI9341 gfx = Adafruit_ILI9341(10, 9);
Grafici plot{ gfx };

// define a nice function to plot
float my_function(size_t x) {
  return sin(x / 10.0) + cos(sqrt(3) * x / 10.0);
}

// y = my_function(x), with x in [0,100)
DataLinear x = DataLinear(100);
DataFunction y = DataFunction(100, my_function);

void setup(void) {
  gfx.begin();
  gfx.setRotation(3);

  plot.clear_screen();
  plot.set_color_map(parula);

  // Plot data as a line. Color line using y
  plot.line(x, y, y);
}

void loop(void) {
}
