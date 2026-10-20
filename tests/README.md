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

## Arduino library compliance

Use [Arduino Lint](https://arduino.github.io/arduino-lint/latest/) to check packaging, metadata and example structure separately from compilation:

```sh
arduino-lint --compliance strict --library-manager update --project-type library --recursive "$PWD"
```

Grafici-GFX is already in the [Library Manager registry](https://github.com/arduino/library-registry/blob/main/repositories.txt), so use `update` rather than `submit`. Pass the absolute library path: Arduino Lint 1.3.0 can incorrectly treat an explicit `.` as the library folder name.

Reviewed against the current [library specification](https://docs.arduino.cc/arduino-cli/library-specification/), [registry requirements](https://github.com/arduino/library-registry/blob/main/FAQ.md) and [API style guide](https://github.com/arduino/docs-content/blob/main/content/learn/08.contributions/01.arduino-library-style-guide/arduino-library-style-guide.md) on 20 October 2026. Arduino Lint 1.3.0 reports no errors after removing unused `ldflags` and `precompiled` fields. The remaining `LS008` warning recommends a `Grafici-GFX.h` header; the established public header remains `Grafici.h`, explicitly selected by `includes=Grafici.h`. All eight example folders pass the structural checks; their build limits are documented above.

The API style guide recommends approachable names, camelCase and simple examples. Existing underscore names remain compatible. Keep the default float examples straightforward and explain precision templates in the dedicated example and guide. Grafici's constructor stores the supplied display reference; initialize the display in `setup()` before plotting.

Before publishing a release, update the version in both `library.properties` and `library.json`, then tag the compliant commit. Version `4.0.0` is already tagged and cannot be reused for an indexed release. Choose a new semantic version that accounts for the changed default missing-data behavior. Keep the registered library name unchanged. The [registry FAQ](https://github.com/arduino/library-registry/blob/main/FAQ.md#how-can-i-publish-a-new-release-once-my-library-is-in-the-list) describes automatic indexing of new tags; a new registry submission is unnecessary.
