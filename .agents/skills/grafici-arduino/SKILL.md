---
name: grafici-arduino
description: Write or explain Grafici-GFX Arduino sketches and diagnose build errors, missing plots, wrong scales, crashes or resource limits on an Arduino display.
---

# Use and debug Grafici on Arduino

The library root is `../../..` relative to this file. Start with [README.md](../../../README.md) and the closest [example](../../../examples/). Check the installed library's headers: an online example or another checkout can expose a different API. For internal fixes, also read [CONTRIBUTE.md](../../../CONTRIBUTE.md) and [grafici-contribute](../grafici-contribute/SKILL.md).

## Establish the actual target

Inspect the sketch and build configuration for the exact board/core, display driver, pins, rotation, buffering and selected Grafici version. Uno R3 and Uno R4 use different targets; a passing build for one does not establish compatibility with the other. Ask for the missing board/display details or the first relevant error only when they cannot be recovered from the available project and logs.

For build failures, reproduce the selected target and inspect verbose output for resolved library paths before changing code or installing dependencies. A standalone C++ source does not receive all `.ino` preprocessing; check required core includes and declarations.

With Arduino CLI, select the library checkout explicitly, substituting the project's actual target and paths:

```sh
arduino-cli compile --fqbn BOARD_FQBN --verbose \
  --library /path/to/Grafici-GFX /path/to/Sketch
```

Add the project's dependency collection with `--libraries` when needed. Check the installed CLI's help for supported options. See Arduino's [build and library resolution rules](https://docs.arduino.cc/arduino-cli/sketch-build-process/); packaging changes should follow the [library specification](https://docs.arduino.cc/arduino-cli/library-specification/).

## Separate the display from the plot

For a blank or corrupted display, first inspect the driver's own initialization and test a native fill or line using the project's existing wiring. Buffered drivers need their update/flush call after drawing; direct-write drivers have different transfer behavior. Grafici accepts an Adafruit GFX backend and does not initialize the hardware.

Once native drawing works, reduce the sketch to a fixed-color line with known data. This helper assumes the display is already initialized and `Grafici.h` is included:

```cpp
void draw_known_plot(Grafici &plot) {
  const float readings[] = {-1.0f, -0.5f, 0.0f, 0.5f, 1.0f};
  DataLinear x(5);
  DataArray<float> y(readings, 5, {-1.0f, 1.0f});
  plot.clear_screen();
  plot.line(x, y, white);
}
```

Expect a white line from bottom-left to top-right. Perform the backend's update call afterwards if it needs one. Reintroduce callbacks, colors, options and custom windows only as needed to locate the failing boundary.

## Diagnose the library behavior

| Symptom | Inspect |
| --- | --- |
| Flattened, clipped or drifting scale | `raw()`, `norm()` and `range()`. Inferred bounds are construction-time snapshots. Explicit bounds clip raw data; constant ranges normalize to zero. Raw zero is not necessarily the baseline of an area or bar. |
| Missing segments or markers | Source lengths and sample `valid()` values, including the color channel. Lines need two valid endpoints; sized scatter markers consume a radius source as well. A subdivision count of zero emits no lines or filled triangles. Use `DataNorm::invalid()` to mark a gap, not a legitimate zero. |
| Interpolation becomes empty or unstable | Knot/view lifetimes, finite values, strictly increasing x, sample capacity and allocation failure. Rebuild splines after knot changes. Autoscaling covers emitted samples, not continuous extrema. |
| Options or palette seem ignored | Fluent option methods return copies; assign or pass the returned value. Keep a palette passed to `set_color_map()` alive. The color source is independent of x/y. |
| Polar shape looks angular or stretched | Normalized x is angle in turns and y is radius. Parent-window aspect ratio stretches the result. Modest powers-of-two subdivision improve curved projection; they do not add source samples. |
| Compile failure with a capturing lambda | The default callback is a function pointer. Opt-in `GRAFICI_USE_STD_FUNCTION` requires a core providing the facility; configure it consistently before including Grafici. |

Keep arrays, adapters, views, callbacks and their referenced state alive until drawing finishes. In particular, store `samples.x()` and `samples.y()` in named variables before constructing a spline that borrows them. Consult the current contract table before assuming historical missing-data behavior.

## Investigate memory and timing

Use [rendering and memory](../../../CONTRIBUTE.md#rendering-and-memory) for retained and temporary costs. The current library uses float data and geometry; it has no FP16 selection option. Prefer borrowed arrays or computed sources where appropriate, known ranges, modest sample counts and low subdivision. Distribution samples, histogram bins and spline coefficients occupy storage even when drawing is lazy.

For resets or corruption, inspect lifetime errors and array bounds alongside stack/heap pressure, including the display driver's buffers and `String`/optional callback allocations. A successful link and the reported global SRAM total do not establish peak memory use. Measure on the actual board; separate source evaluation, geometry and display transfer time before optimizing. Do not propose a full framebuffer as a default memory-saving fix.

Use Grafici-Test to isolate data/geometry behavior when hardware is unavailable. Its host types and file buffer are not the Arduino ABI, memory budget, bus or display. State what was reproduced, what was compiled, and what remains a hardware observation; do not present an untested wiring assumption as a library defect.
