# Grafici-GFX

[![Arduino Library](https://www.ardu-badge.com/badge/Grafici-GFX.svg)](https://www.ardu-badge.com/Grafici-GFX)
[![License: Apache 2.0](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)

Grafici is an Arduino plotting library for displays supported by **Adafruit GFX**. Draw lines, filled areas, bars and scatter plots using reusable data sources, color maps and Cartesian or polar windows.

![Example Plot](https://raw.githubusercontent.com/cattanimarco/Grafici-Test/master/imgs/examples/line_from_array.jpg)

## Design

Data sources provide values and their ranges independently of the plotter and display. Arrays, functions, distributions, histograms and interpolators can feed the same plotting calls. Separate sources can control x, y, color and marker size.

The common interface uses normalized values: each source maps its raw range into `[0,1]`, and windows transform logical coordinates into normalized display coordinates. Pixel resolution enters at the display boundary, so data and plot layouts can be reused across display sizes. Raw values and floating-point intermediates remain signed and may exceed 1; normalization does not restrict the scalar format to `[0,1]`.

## Getting started

In the Arduino IDE, open **Sketch → Include Library → Manage Libraries**, search for **Grafici-GFX** and install it. Alternatively, copy this library into your Arduino libraries folder. Install **Adafruit GFX Library** and the driver for your display as well. For PlatformIO, add:

```ini
lib_deps = Grafici-GFX
```

Include `Grafici.h` and pass your `Adafruit_GFX` display to `Grafici`; initialize the display before drawing. The library supports C++11.

This example uses an ILI9341 display; install **Adafruit ILI9341** and adjust the driver, pins and rotation for your hardware:

```cpp
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <Grafici.h>

Adafruit_ILI9341 display(10, 9); // Chip select, data/command.
Grafici plot(display);

float readings[] = {8.4f, 12.9f, 21.6f, 26.6f};
DataArrayXY<float> data(readings, 4, {0, 30});

void setup()
{
    display.begin();
    display.setRotation(3);
    plot.clear_screen();

    auto x = data.x();
    auto y = data.y();
    plot.line(x, y, white, full_screen, plot_options.set_axis(4, 4));
}

void loop() {}
```

`DataArrayXY` uses sample indices for x and the supplied array for y. Here, y maps the fixed raw range `[0,30]` to the plot height; omitting that range discovers bounds from the data. Arrays are borrowed without copying, so keep them alive while their sources are used. Values outside an explicit range are clipped; missing samples leave gaps.

## Plotting and examples

Use `line()`, `area()`, `bar()` or `scatter()` with interchangeable normalized sources. Choose a constant color or supply a color source through a palette. `PlotOptions` controls axes, bar fill/thickness, marker styles and subdivision. `Window` arranges subplots and rotations; `PolarWindow` projects the same logical geometry into polar coordinates.

| Example | Demonstrates |
| --- | --- |
| [Line from a function](examples/line_from_function/line_from_function.ino) | Independent x/y sources and data-driven color. |
| [Animated line](examples/line_animated/line_animated.ino) | Updating a function and redrawing. |
| [Bars from an array](examples/bars_from_c_array/bars_from_c_array.ino) | Explicit ranges, filled bars and axes. |
| [Filled areas](examples/area_from_c_array/area_from_c_array.ino) | Combining datasets and plot styles. |
| [Polar plots](examples/lines_from_functions_polar/lines_from_functions_polar.ino) | Reusing sources with a different window projection. |
| [Scatter and histogram](examples/scatter_and_histogram_from_distribution/scatter_and_histogram_from_distribution.ino) | Distributions, marker channels and grouped counts. |
| [Float16 line](examples/fp16_line/fp16_line.ino) | Selecting a smaller floating-point representation. |

## Memory and precision

`float` is the default and needs no configuration. Use it when precision, numerical range, CPU time or flash matter more than sample storage. Optional `grafici::Float16` stores each value in **2 bytes instead of 4**, at lower precision and with a maximum finite magnitude of 65,504. Conversions can add CPU work and flash usage.

To compress only the quick-start sample array, change `float readings[]` to `grafici::Float16 readings[]` and `DataArrayXY<float>` to `DataArrayXY<grafici::Float16>`. Keep `Grafici` unchanged. To select Float16 throughout the pipeline, use a shared scalar alias, `using Real = grafici::Float16;`, with `GraficiT<Real>` and `DataArrayXY<Real, Real>`; the [precision guide](PRECISION.md) explains the other typed classes, tradeoffs and measured sizes.

Budget for sample storage, spline workspace, rendering scratch and any display-driver buffers. Grafici does not require a framebuffer. Increasing subdivision adds drawing work, especially for filled shapes. Six examples fit Uno R3 flash in the current build audit; the area and scatter/histogram examples need more flash or reduced complexity. The original examples were display-tested on Uno R4 Minima with the Adafruit 2.8-inch TFT Touch Shield.

## Documentation and testing

- [Architecture](ARCHITECTURE.md): Mermaid diagrams, the normalized pipeline and efficiency improvements.
- [Boundary contracts](CONTRACTS.md): valid/missing data, empty inputs, interpolation and geometric clipping.
- [Test instructions](tests/README.md): regression coverage, Arduino builds and library compliance/release checks. Run the included host checks with `python3 tests/run_checks.py --sanitize`.
- [Correctness patches](patches/correctness/README.md): explanations, application order and Uno R3 build sizes.

Additional tests are in [Grafici-Test](https://github.com/cattanimarco/Grafici-Test). Design notes and future ideas are available in the [project notes](https://cattanimarco.github.io/notes/Grafici).

See the [Wiki](https://github.com/cattanimarco/Grafici-GFX/wiki) for API documentation. Contributions are welcome through pull requests; run the regression checks before submitting changes.

Licensed under [Apache 2.0](LICENSE).
