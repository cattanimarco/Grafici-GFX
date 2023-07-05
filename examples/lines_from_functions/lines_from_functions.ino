#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"  // display-specific library
#include "Grafici.h"

Adafruit_ILI9341 gfx = Adafruit_ILI9341(10, 9);
Grafici plot{ gfx };

constexpr size_t num_elements = 360;

// define a set of nice functions to plot functions
DataFunction fn_sin(num_elements, [](size_t idx) -> float {
  return sin(idx / 30.0 * M_PI);
});
DataFunction fn_zig_zag(num_elements, [](size_t idx) -> float {
  return acos(cos(idx / 30.0 * M_PI));
});
DataFunction fn_square(num_elements, [](size_t idx) -> float {
  return ((idx / 30) % 2 == 0) ? 0 : 1;
});
DataFunction fn_pixel_sin(num_elements, [](size_t idx) -> float {
  return round(2 * sin(idx / 30.0 * M_PI));
});
DataFunction fn_beat(num_elements, [](size_t idx) -> float {
  return idx % 17 == 0 ? 0 : (idx % 23 == 0 ? 1 : .5);
});

// rescale y values to fit all the funtions in the same plot
DataResize y_1(fn_sin, { 0.01, 0.19 });
DataResize y_2(fn_zig_zag, { 0.21, 0.39 });
DataResize y_3(fn_square, { 0.41, 0.59 });
DataResize y_4(fn_pixel_sin, { 0.61, 0.79 });
DataResize y_5(fn_beat, { 0.81, 0.99 });

DataLinear x(num_elements);

void setup(void) {
  gfx.begin();
  gfx.setRotation(3);

  plot.clear_screen();
  plot.set_color_map(rainbow);

  // first plot will draw also the axis
  plot.line(x, y_1, y_1, full_screen, plot_options.set_axis(10, 10, gunpowder));

  // we do not clear the screen so that we can see show multiple plots at the same time
  plot.line(x, y_2, y_2);
  plot.line(x, y_3, y_3);
  plot.line(x, y_4, y_4);
  plot.line(x, y_5, y_5);
}

void loop(void) {
}
