# Regression checks

Run all host checks from the repository root with Python 3 and a C++11 compiler:

```sh
python3 tests/run_checks.py --sanitize
```

Omit `--sanitize` when the compiler has no UndefinedBehaviorSanitizer support. `--cxx clang++` or the `CXX` environment variable selects another compiler. The runner uses C++11, strict warnings and temporary output files. No Arduino installation is required; drawing tests use the included GFX call recorder. The recorder checks coordinates and calls, without emulating hardware rasterization.

| Check | Coverage |
| --- | --- |
| `data_spline_bounds.cpp` | Guard every workspace allocation, inject all five allocation failures, reject unsupported coefficient/source counts, preserve cleanup and avoid uncovered-knot reads. |
| `spline_autoscale.cpp` | Preserve unclipped cubic overshoot before discovering the output range; retain explicit clipping with autoscaling disabled. |
| `interpolation_bounds.cpp` | Both endpoints, one/zero outputs, empty/short inputs, uncovered domains, duplicate/reversed/non-finite knots and decreasing y values. |
| `scatter_lengths.cpp` | Short/empty radius and color sources; radius-independent dots and composite markers. |
| `color_map_indices.cpp` | Floating-point generated-palette indexing, wrapping, large indices and zero-size handling. |
| `color_blending.cpp` | All 65,536 midpoint channel pairs, nearest/ties-up blending and constant-color subdivision; all 256 channel values retain the former RGB565 quantization bins. |
| `data_contracts.cpp` | Explicit missing-data validity without added payload, range extremes, finite-only bounds discovery, empty sources/histograms, invalid classes/slices, polar parent preservation and gaps. |
| `display_clipping.cpp` | Signed pixels, geometric line/triangle intersections, non-finite/extreme coordinates, dimensions, rotation/polar transforms, native clear and 2,000 guarded polygon cases. |
| `numeric_precision.cpp` | Every binary16 encoding and finite rounding interval; typed sources, adapters, storage sizes and arithmetic outside `[0,1]`. |
| `precision_plotting.cpp` | Both complete precision families and the existing float API across all plotters. |

The runner also requires `ColorMapArray<0>` and `DataHistogramXY<0>` to fail compilation with the intended static-assert messages. Keep assertions enabled.

For a single check:

```sh
c++ -std=c++11 -Wall -Wextra -Werror -pedantic -I tests/support -I src tests/display_clipping.cpp -o /tmp/grafici-clipping
/tmp/grafici-clipping
```

## Arduino C++11 validation

Install the AVR core and the display libraries used by the examples. Build a representative sketch with the standard Uno R3 GNU C++11 recipe:

```sh
arduino-cli compile --fqbn arduino:avr:uno --library . examples/fp16_line
```

`--library .` explicitly selects this checkout. The examples use explicit template arguments, integer sample counts, and capture-free function-pointer callbacks. All eight examples compile with AVR GNU C++11, including a check without `-fpermissive` and with narrowing errors enabled. Six fit Uno R3 flash; the area and scatter/histogram examples exceed it. See [the build audit](../patches/correctness/README.md#avr-build-audit) for sizes. These were originally display-tested on Uno R4 Minima.

A separate host integration using the installed actual Adafruit GFX canvas confirmed full clipped-triangle coverage, horizontal-line rasterization and native clearing for float/FP16. Linked board sizes do not measure runtime stack/heap peaks or physical display timing. Clipping scratch and spline workspace must be included in an application's SRAM budget.
