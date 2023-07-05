#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"  // display-specific library
#include "Grafici.h"

Adafruit_ILI9341 gfx{ 10, 9 };
Grafici plot{ gfx };

static unsigned int offset = 0;
const float x_resolution = gfx.width() / 10.0;

// define functions for x and y
DataLinear   x { x_resolution };
DataFunction y { x_resolution, [offset](size_t x) -> float { return sin((x + offset) / (x_resolution / 10.0)) + cos(sqrt(3) * (x + offset) / (x_resolution / 10.0)); } };

void setup(void) 
{
  gfx.begin();
  gfx.setRotation(3);

  plot.clear_screen();
  plot.set_color_map(rainbow);
}

void loop(void) 
{
  // add offset to y to animate plot
  offset++;

  // plot and wait (use y values to color the plot)
  plot.line(x, y, y);
  delay(10);

  // re-plot the same data in black to clear the screen
  // this is usually faster than calling plot.clear_screen()
  plot.line(x, y, black);
}
