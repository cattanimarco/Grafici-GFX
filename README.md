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

### Platform IO
Add to your `platformio.ini`:
```ini
lib_deps = Grafici-GFX
```

## Quick Start

```cpp
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include "Grafici.h"

Adafruit_ILI9341 gfx = Adafruit_ILI9341(10, 9);
Grafici plot{ gfx };

// Create data source from function
float my_function(size_t x) {
  return sin(x / 10.0) + cos(sqrt(3) * x / 10.0);
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

## Examples

### Statistical Visualization
Create a scatter plot with histogram using normal distribution data:

```cpp
constexpr size_t data_size = 300;
constexpr size_t histogram_bins = 20;

// Generate random data with normal distribution
DataLinear x(data_size);
DataDistributionNormal<data_size> y(84);
DataConstant marker_size(data_size, 0.01);

void setup(void) {
  gfx.begin();
  gfx.setRotation(3);
  plot.clear_screen();
  plot.set_color_map(cmy);

  // Left window: Scatter plot (0-74% width)
  auto left_window = full_screen.sub_window({ 0, .74 }, { 0, 1 });
  auto left_opts = plot_options.set_axis(histogram_bins, 1, silver)
                              .segments(10)
                              .scatter_style("x");
  plot.scatter(x, y, y, marker_size, left_window, left_opts);

  // Right window: Histogram (76-100% width)
  auto right_window = full_screen.sub_window({ .76, 1 }, { 0, 1 })
                                .transform(WindowTransform::ccw_90_rotation);
  auto right_opts = plot_options.set_axis(5, histogram_bins, silver)
                               .bar_filled(true)
                               .thickness(0.5);
  
  // Plot histogram
  DataHistogramXY<histogram_bins> data_hist{ y };
  plot.bar(data_hist.x(), data_hist.y(), data_hist.x(), 
          right_window, right_opts);
}
```

### Polar Plots
Create a polar plot with multiple functions:

```cpp
DataLinear r(100);  // Radius data
DataFunction theta1(100, [](size_t x) { 
  return sin(x / 10.0); 
});
DataFunction theta2(100, [](size_t x) { 
  return cos(x / 8.0); 
});

void setup(void) {
  gfx.begin();
  plot.clear_screen();
  plot.set_color_map(heat);

  // Create polar window
  auto polar = PolarWindow(full_screen);
  auto opts = plot_options.set_axis(10, 10, white);

  // Plot multiple functions
  plot.line(r, theta1, theta1, polar, opts);
  plot.line(r, theta2, theta2, polar, opts);
}
```

### Animated Line Plot
Create an animated line plot:

```cpp
DataLinear x(100);
float phase = 0;

void setup(void) {
  gfx.begin();
  plot.set_color_map(rainbow);
}

void loop(void) {
  plot.clear_screen();
  
  // Create animated function
  DataFunction y(100, [](size_t x) {
    return sin(x / 10.0 + phase);
  });
  
  plot.line(x, y, y);
  phase += 0.1;
  delay(50);
}
```

### Area Plot from Array
Create an area plot from a C array:

```cpp
const float data[] = {0, 1, 2, 1, 0, -1, -2, -1};
DataArray y(data, 8);
DataLinear x(8);

void setup(void) {
  gfx.begin();
  plot.clear_screen();
  plot.set_color_map(temperature);
  
  auto opts = plot_options.set_axis(8, 4, white);
  plot.area(x, y, y, full_screen, opts);
}
```

For more examples, check out the [examples](examples/) directory and our [Wiki](https://github.com/cattanimarco/Grafici-GFX/wiki).

## Documentation

Visit our [Wiki](https://github.com/cattanimarco/Grafici-GFX/wiki) for detailed documentation, including:
- Complete API reference
- Example explanations
- Advanced usage guides
- Window system tutorial

## Hardware Compatibility

### Tested Hardware
- Arduino UNO R4 Minima
- Adafruit 2.8" TFT Touch Shield

### Memory Requirements
Some examples may exceed available memory on older Arduino boards. The library is optimized for modern Arduino boards with adequate RAM.

## Testing

### Unit Tests
The library's test suite is maintained in the [Grafici-Test](https://github.com/cattanimarco/Grafici-Test) repository. It provides:
- Automated testing of library features
- Example image generation
- Documentation verification
- JPEG/PNG output for visual testing

### System Tests
All examples are tested on actual hardware to ensure real-world compatibility.

## Contributing

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Run the test suite
5. Submit a pull request

## Future Development

Check our [project notes](https://cattanimarco.github.io/notes/Grafici) for upcoming features and development ideas.

## License

This project is licensed under the Apache License 2.0 - see the [LICENSE](LICENSE) file for details.

## Dependencies

- [Adafruit GFX Library](https://github.com/adafruit/Adafruit-GFX-Library)
