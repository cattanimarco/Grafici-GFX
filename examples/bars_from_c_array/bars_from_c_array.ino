#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"  // Hardware-specific library
#include "Grafici.h"

Adafruit_ILI9341 gfx = Adafruit_ILI9341(10, 9);
Grafici plot{ gfx };

// raw temperature data
// https://www.metoffice.gov.uk/pub/data/weather/uk/climate/stationdata/cambridgedata.txt
float cambridge_max_temp_22[] = { 8.4, 10.9, 12.9, 15.1, 18.9, 21.6, 26.1, 26.6, 20.4, 18.3, 12.6, 7.0 };
float cambridge_min_temp_22[] = { 1.2, 3.6, 3.7, 4.3, 8.9, 10.2, 13.3, 13.4, 10.7, 9.4, 7.0, 0.1 };

// create dataset from raw data and set minimum (0) and maximum (30) temperature values
DataArray<float> max_temps{ cambridge_max_temp_22, 12, { 0, 30 } };
DataArray<float> min_temps{ cambridge_min_temp_22, 12, { 0, 30 } };

// x values in [0,11] (position of the bar horizzontal center)
// range in [-0.5,11.5] to fully show the first and last bars
DataLinear x{ 12, { -0.5, 11.5 } };

void setup(void) {
  gfx.begin();
  gfx.setRotation(3);

  plot.clear_screen();
  plot.set_color_map(temperature);

  // set barplot properties
  auto opts = plot_options.bar_filled(true).set_axis(6, 12, gunpowder);

  // bar plot max temperatures using temperature as a color
  plot.bar(x, max_temps, max_temps, full_screen, opts);

  // bar plot min temperatures using black as a color (mask)
  plot.bar(x, min_temps, black, full_screen, opts);
}

void loop(void) {
}
