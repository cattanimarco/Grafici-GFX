# Grafici-GFX

[![Arduino Library](https://www.ardu-badge.com/badge/Grafici-GFX.svg)](https://www.ardu-badge.com/Grafici-GFX)
[![License: Apache 2.0](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)

A powerful data visualization library for Arduino displays supporting the Adafruit GFX interface. Create beautiful plots, charts, and visualizations with minimal code.

![Example Plot](https://raw.githubusercontent.com/cattanimarco/Grafici-Test/master/imgs/examples/line_from_array.jpg)

## Features

- 📊 Multiple plot types:
  - Line plots
  - Scatter plots
  - Bar charts
  - Area plots
  - Histograms
  - Polar plots
- 🎨 Customizable color schemes
- 📐 Support for both rectangular and round displays
- 📏 Normalized coordinate system
- 🔄 Data processing and transformation
- 🎯 Window-based plotting regions

## Installation

### Arduino IDE

1. Open Arduino IDE
2. Go to `Sketch` > `Include Library` > `Manage Libraries` (`SHIFT + CMD + I`)
3. Search for `Grafici`
4. Select `Grafici-GFX` and click `Install`

Accept the Adafruit GFX dependency installation, then install the library for your display controller. The examples use [Adafruit ILI9341](https://github.com/adafruit/Adafruit_ILI9341).

### PlatformIO

Add this [Git dependency](https://docs.platformio.org/en/latest/projectconf/sections/env/options/library/lib_deps.html) to your environment's `platformio.ini` section, along with your display driver:

```ini
lib_deps =
  https://github.com/cattanimarco/Grafici-GFX.git
  adafruit/Adafruit ILI9341
```

## Quick Start

This sketch uses an ILI9341 display with chip-select pin 10 and data/command pin 9. Adapt the driver, pins and initialization to your hardware. Drivers with buffered output also need their display-update call after plotting.

```cpp
#include <math.h>
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include "Grafici.h"

Adafruit_ILI9341 gfx = Adafruit_ILI9341(10, 9);
Grafici plot{ gfx };

// Create data source from function
float my_function(size_t x) {
  return sinf(x / 10.0f) + cosf(sqrtf(3.0f) * x / 10.0f);
}

DataLinear x = DataLinear(100);
DataFunction y = DataFunction(100, my_function);

void setup(void) {
  gfx.begin();
  gfx.setRotation(3);

  plot.clear_screen();
  plot.set_color_map(parula);
  plot.line(x, y, y);  // Plot data as a line, color by y value
}

void loop(void) {}
```

## Working with Data

`DataArray<T>` borrows an existing array; `DataFunction` computes values when read. Both expose raw values through `DataNorm::raw()` and normalized values through `norm()`. Sources can be reused across plot types, with separate channels for position, color and marker size. Windows use normalized coordinates with `(0,0)` at the bottom-left. Raw values can be negative or exceed one; samples use `float` values and range bounds.

Keep arrays, borrowed sources and palettes alive while they are used. Inferred ranges are fixed at construction; supply explicit ranges for a stable scale when data changes. Plot options return modified copies, so assign or pass the result of a fluent chain.

## Examples

These snippets reuse the includes and `gfx`/`plot` declarations from Quick Start. Replace its data declarations, `setup()` and `loop()` with the selected example.

### Statistical Visualization

Create a scatter plot with histogram using normal distribution data:

```cpp
constexpr size_t data_size = 64;
constexpr size_t histogram_bins = 20;

// Generate random data with normal distribution
DataLinear x(data_size);
DataDistributionNormal<data_size> y(84);
DataConstant marker_size(data_size, 0.01f);

void setup(void) {
  gfx.begin();
  gfx.setRotation(3);
  plot.clear_screen();
  plot.set_color_map(cmy);

  // Left window: Scatter plot (0-74% width)
  auto left_window = full_screen.sub_window({ 0, .74 }, { 0, 1 });
  auto left_opts = plot_options.set_axis(histogram_bins, 1, silver)
                              .segments(8)
                              .scatter_style("x");
  plot.scatter(x, y, y, marker_size, left_window, left_opts);

  // Right window: Histogram (76-100% width)
  auto right_window = full_screen.sub_window({ .76, 1 }, { 0, 1 })
                                .transform(WindowTransform::ccw_90_rotation);
  auto right_opts = plot_options.set_axis(5, histogram_bins, silver)
                               .bar_filled(true)
                               .thickness(0.5f);

  // Plot histogram
  DataHistogramXY<histogram_bins> data_hist{ y };
  plot.bar(data_hist.x(), data_hist.y(), data_hist.x(),
          right_window, right_opts);
}

void loop(void) {}
```

### Polar Plots

Create a polar plot with multiple functions:

```cpp
DataLinear angle(100);  // Normalized x spans one turn.
DataFunction radius1(100, [](size_t x) -> float {
  return sinf(x / 10.0f);
});
DataFunction radius2(100, [](size_t x) -> float {
  return cosf(x / 8.0f);
});

void setup(void) {
  gfx.begin();
  plot.clear_screen();
  plot.set_color_map(heat);

  // Create polar window
  PolarWindow polar;
  auto opts = plot_options.set_axis(10, 10, white).segments(8);

  // Plot multiple functions
  plot.line(angle, radius1, radius1, polar, opts);
  plot.line(angle, radius2, radius2, polar, opts);
}

void loop(void) {}
```

### Animated Line Plot

Create an animated line plot:

```cpp
DataLinear x(100);
float phase = 0.0f;

void setup(void) {
  gfx.begin();
  plot.set_color_map(rainbow);
}

void loop(void) {
  plot.clear_screen();

  // A known range keeps the scale fixed and avoids a bounds scan each frame.
  DataFunction y(100, [](size_t x) -> float {
    return sinf(x / 10.0f + phase);
  }, {-1.0f, 1.0f});

  plot.line(x, y, y);
  phase += 0.1f;
  delay(50);
}
```

### Area Plot from Array

Create an area plot from a C array:

```cpp
const float data[] = {0, 1, 2, 1, 0, -1, -2, -1};
DataArray<float> y(data, 8);
DataLinear x(8);

void setup(void) {
  gfx.begin();
  plot.clear_screen();
  plot.set_color_map(temperature);

  auto opts = plot_options.set_axis(8, 4, white);
  plot.area(x, y, y, full_screen, opts);
}

void loop(void) {}
```

Area plots and bars start at normalized zero, corresponding to the lower bound of the source range.

For more examples, check out the [examples](examples/) directory and our [Wiki](https://github.com/cattanimarco/Grafici-GFX/wiki).

## Callbacks with captured state

`DataFunction` uses raw function pointers by default, keeping the existing memory footprint and AVR support. On cores that provide `<functional>` (such as ESP32 and RP2040), enable capturing lambdas and callable objects before including Grafici:

```cpp
#define GRAFICI_USE_STD_FUNCTION 1
#include <Grafici.h>

void draw_with_offset(Grafici &plot, float offset) {
  DataLinear x(100);
  DataFunction y(100, [offset](size_t i) -> float {
    return sinf(i / 10.0f) + offset;
  });
  plot.line(x, y, y);
}
```

Use `[this]` to call member functions. The callback is stored by value; referenced objects must outlive the source. Set the option consistently across translation units. `std::function` uses more storage and may allocate heap memory. Both constructors support it; supply an explicit range when captured state can change the output bounds. Empty callbacks produce zero samples.

## Data validity

Default `DataNorm` values and `DataNorm::invalid()` represent missing samples; `DataNorm(0.0f)` is a legitimate zero. Use `valid()` to distinguish them. Missing line/area samples leave gaps. Interpolation with two or more outputs includes both endpoints, and projected geometry is clipped to the physical display before pixel conversion. See [boundary contracts](CONTRIBUTE.md#boundary-and-invalid-data-contracts).

## Documentation

See [the contributor guide](CONTRIBUTE.md) for module diagrams, source composition, boundary contracts, extension points and memory costs. The [Wiki](https://github.com/cattanimarco/Grafici-GFX/wiki) provides background concepts and additional plotting walkthroughs.

## Hardware Compatibility

### Tested Hardware

- Arduino UNO R4 Minima
- Adafruit 2.8" TFT Touch Shield

### Memory Requirements

Grafici draws primitives without retaining a framebuffer; your display driver may use one. Borrowed arrays and computed sources avoid an extra sample buffer, while distributions, histograms and splines retain their own data or coefficients. On small boards, keep sample counts and subdivision low, and budget for temporary workspace and stack as well as retained storage. See [rendering and memory](CONTRIBUTE.md#rendering-and-memory).

The bundled area and scatter/histogram examples exceed Uno R3 flash in the build audit and need more flash or reduced complexity. Compile the chosen sketch for your board before selecting its sample count and plot options.

## Testing

### Unit Tests

Tests live separately in [Grafici-Test](https://github.com/cattanimarco/Grafici-Test), which includes Grafici-GFX as a submodule. Its [build instructions](https://github.com/cattanimarco/Grafici-Test#building-and-running-tests) cover rendering to image files without display hardware. See [verification](CONTRIBUTE.md#verification) for focused regressions and board checks.

### System Tests

Host regressions and AVR builds complement the original Uno R4 Minima display tests. Measure display timing and peak SRAM with your board, driver and plot configuration.

## Contributing

See [the contributor guide](CONTRIBUTE.md) for architecture, boundary contracts and memory constraints.

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Run the test suite
5. Submit a pull request

## Future Development

See [open issues](https://github.com/cattanimarco/Grafici-GFX/issues) for feature discussions and reported problems.

## License

This project is licensed under the Apache License 2.0 - see the [LICENSE](LICENSE) file for details.

## Dependencies

- [Adafruit GFX Library](https://github.com/adafruit/Adafruit-GFX-Library)
- A display-specific driver implementing Adafruit GFX, such as [Adafruit ILI9341](https://github.com/adafruit/Adafruit_ILI9341).
