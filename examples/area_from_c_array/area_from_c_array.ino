#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"  // display-specific library
#include "Grafici.h"

Adafruit_ILI9341 gfx = Adafruit_ILI9341(10, 9);
Grafici plot{ gfx };

constexpr size_t num_stars = 100;

const float cambridge_daylight[] = { 7.49, 9.07, 10.54, 13.00, 14.56, 16.27, 16.41, 15.29, 13.36, 11.36, 9.35, 8.04 };

auto daylight_data = DataArrayXY(cambridge_daylight, 12, { 0, 24 });
auto star_positions_x = DataDistributionUniform<num_stars>(84);
auto star_positions_y = DataDistributionUniform<num_stars>(48);
auto star_sizes = DataConstant(num_stars, 0.01);

void setup(void) {
  gfx.begin();
  gfx.setRotation(3);

  plot.clear_screen();
  plot.set_color_map(black_and_white);

  // draw stars
  plot.scatter(star_positions_x, star_positions_y, white, star_sizes, full_screen, plot_options.scatter_style("."));

  plot.area(daylight_data.x(), daylight_data.y(), daylight_data.y());
}

void loop(void) {
}
