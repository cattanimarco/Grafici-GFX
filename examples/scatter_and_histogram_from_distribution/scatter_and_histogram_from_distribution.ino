#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"  // Hardware-specific library
#include "Grafici.h"

Adafruit_ILI9341 gfx = Adafruit_ILI9341(10, 9);
Grafici plot{ gfx };

constexpr size_t data_size = 300;
constexpr size_t histogram_bins = 20;

// plot generated random data with normal distribution
DataLinear x(data_size);
DataDistributionNormal<data_size> y(84);

void setup(void) {
  gfx.begin();
  gfx.setRotation(3);

  plot.clear_screen();
  plot.set_color_map(cmy);

  // define a screen region between 0% and 74% of the total width and between 0% and 100% of the total height
  auto left_window = full_screen.sub_window({ 0, .74 }, { 0, 1 });
  auto left_opts = plot_options.set_axis(histogram_bins, 1, silver).segments(10).scatter_style("x");

  // use constant fir the marker size
  DataConstant s(data_size, 0.01);

  // Scatter plot data. Color markers using y
  plot.scatter(x, y, y, s, left_window, left_opts);

  // define a screen region between 76% and 100% of the total width and between 0% and 100% of the total height
  auto right_window = full_screen.sub_window({ .76, 1 }, { 0, 1 }).transform(WindowTransform::ccw_90_rotation);
  auto right_opts = plot_options.set_axis(5, histogram_bins, silver).bar_filled(true).thickness(0.5);

  // compute the histogram of y
  DataHistogramXY<histogram_bins> data_hist{ y };

  // plot histogram bars. Color the bars using y
  plot.bar(data_hist.x(), data_hist.y(), data_hist.x(), right_window, right_opts);
}

void loop(void) {
}