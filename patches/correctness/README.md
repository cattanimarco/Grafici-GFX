# Correctness and portability patches

The fixes cover every item in [ARCHITECTURE.md](../../ARCHITECTURE.md#5-correctness-and-portability-fixes). Spline bounds and autoscaling share one patch; the remaining fixes keep their original item numbers. Every patch includes its explanation, memory implications and validation in the commit message. **The fixes are already applied in this checkout.**

## Application order

[01-spline-fixes.patch](01-spline-fixes.patch) combines the allocation/bounds and autoscaling fixes against `origin/main` at `575ef29`. Apply it first, then the rebased [float16.patch](../float16.patch), followed by **03–09** in order. The former patch 02 is merged into 01.

The `series` file includes every required patch, including `../float16.patch`. From a clean `575ef29` checkout containing these exported files:

```sh
while IFS= read -r patch; do
    git apply --check "patches/correctness/$patch" || exit 1
    git apply "patches/correctness/$patch" || exit 1
done < patches/correctness/series
python3 tests/run_checks.py --sanitize
```

For the spline fixes alone, apply 01 to `575ef29`. These exports replace the previous spline and Float16 patch versions. Reorganizing the patches does not change the library sources already present in this checkout.

## Changes and explanations

| Item / patch | Problem and resulting behavior | Memory and computation |
| --- | --- | --- |
| [01: Spline bounds and autoscaling](01-spline-fixes.patch) | Allocate full `n+1` solver elements; reject unsupported knot/output counts, guard knot pairs and release partial allocations. Discover the output range from unclipped cubic evaluations before constructing normalized samples, preserving overshoot. Explicit non-autoscaled clipping remains supported. | Correct temporary solver payload is `20*n+12` bytes, `n=source_count-1`. Retained coefficient arrays do not grow; the shared Horner evaluator needs constant-size locals. Autoscaling covers emitted samples, not continuous extrema. Guarded allocations, all five allocation failures and overshoot regressions accompany the patch; Float16 extends their coverage to both precision families. |
| [03: Interpolation boundaries](03-interpolation-boundaries.patch) | Include both endpoints with `i/(M-1)` for `M>=2`; one output returns the first knot. Reject fewer than two knots, duplicates, reversed/non-finite x, and excess spline intervals. Uncovered domains return missing samples. Decreasing y remains supported. | Validate knots once, retain bounded bin searches, and remove unused output-index range metadata. Borrowed sources must remain stable. Tests cover endpoints, short sources and invalid knots. |
| [04: Scatter size bounds](04-scatter-size-bounds.patch) | Radius-dependent markers stop at the shortest x/y/color/radius source. Dots need no radius; composite styles continue their dots when radii end. | No buffer. Read the style string once per draw, reducing temporary copies. Guarded sources verify that no channel is read out of bounds. |
| [05: Palette indexing](05-palette-indexing.patch) | Replace generated-palette integer division with a floating-point fraction after index wrapping. Zero-size generated maps report invalid and return black; `ColorMapArray<0>` fails compilation. | No added retained state or allocation. Tests cover distinct entries, wrapped and large indices, and zero/one-size cases. |
| [06: Color rounding](06-color-rounding.patch) | Separately truncating both half-colors darkened identical colors. Use widened integer `(a+b+1)/2`; linear blends round nearest with ties upward and preserve endpoints. RGB565 uses integer scaling with the previous floor bins. | No object growth or buffer; integer midpoint/RGB565 arithmetic avoids floating-point work. Exhaustive channel-pair and RGB565 regressions verify rounding and constant-color subdivision. |
| [07: Boundary contracts](07-boundary-contracts.patch) | Define constant/reversed ranges, empty/null sources, empty histograms, zero slices and non-finite inputs. Missing data gets an explicit `valid()` query and creates plotting gaps. Reject zero histogram bins at compile time and preserve parent transforms in polar slices. See [CONTRACTS.md](../../CONTRACTS.md). | Invalidity uses existing reversed-range metadata: `DataNorm` stays 12 bytes for float and 6 for FP16. No validity array or added heap allocation. Finite checks add computation, with direct exponent-bit checks for FP16. Regression coverage includes range extremes and unsafe-conversion boundaries. |
| [08: Signed pixels and clipping](08-signed-geometric-clipping.patch) | Project without clamping each vertex; clip finite lines and triangles to the physical display, then convert to signed `int16_t` pixels. Reject invalid projections/dimensions. This preserves intersections instead of drawing false edge lines. Default clearing uses native GFX fill. | Lines use constant-size locals; triangles use two seven-point buffers, **112 bytes of FP32 coordinate payload**, plus locals/backend stack. No heap or framebuffer. Native default clear avoids retaining triangle clipping in simple line sketches. Tests include extreme coordinates, polar/rotated windows and guarded polygon cases. |
| [09: C++11 portability](09-cpp11-portability.patch) | Give the area source explicit template arguments, use integer resolution in animation and a capture-free callback for its global offset. Remove redundant function-definition semicolons flagged by older AVR compilers. Add a repeatable host-check runner and update documentation/build measurements. | No added runtime buffers or allocation. All eight examples compile under AVR GNU C++11; linked flash limits are below. |

## Observable contracts

`DataNorm()` now means missing data; a valid zero is explicitly `DataNorm(0, {0,0})`. Query `valid()` rather than comparing against an old zero sentinel. Reversed ranges are invalid until sorted; constant finite ranges are valid and normalize to zero. Missing line/area samples leave gaps. Neither the float nor FP16 scalar is restricted to `[0,1]`.

Interpolation now includes its final endpoint. FP16 rounding can collapse distinct knots; validation rejects the collapsed input instead of dividing by zero. Finite but ill-conditioned splines can still lose accuracy. Autoscaling examines sampled outputs.

Clipping uses the **physical display** boundary. A subwindow supplies a transform, not an additional stencil mask, so markers can extend outside that subwindow while remaining on display. Pixel conversion still truncates toward zero after clipping. Explicit-window clears retain projected geometry; the no-argument clear uses native fill.

## Validation

The ten C++11 runtime checks pass with strict warnings, UndefinedBehaviorSanitizer and float-cast-overflow checking. Two additional fixtures must fail compilation with the intended zero-palette/zero-bin diagnostics. [Test instructions](../../tests/README.md) describe coverage and commands. A separate check using the installed actual `GFXcanvas16` confirmed clipped-triangle coverage, horizontal-line rasterization and native clear for float/FP16.

The exported series was applied in order to a clean `575ef29` fixture: combined spline fix, rebased Float16, then 03–09. Resulting sources/tests match this checkout, and the host suite passes from the applied fixture. Both standalone spline regressions also pass before applying Float16; all four precision-stage regressions pass after it.

## AVR build audit

Arduino Uno R3, AVR core 1.8.8, AVR GCC 7.3.0, standard `-Os`/LTO, Adafruit GFX 1.11.10 and ILI9341 1.6.1. All eight sketches compile as GNU C++11; a separate syntax check also passes without `-fpermissive` and with narrowing errors enabled.

| Example | Flash bytes | Static SRAM bytes | Uno R3 flash fit |
| --- | ---: | ---: | --- |
| `area_from_c_array` | 37,998 | 1,377 | Exceeds 32,256 |
| `bars_from_c_array` | 32,194 | 591 | Fits, only 62 bytes spare |
| `fp16_line` | 30,304 | 496 | Fits |
| `line_animated` | 26,616 | 491 | Fits |
| `line_from_function` | 26,440 | 455 | Fits |
| `lines_from_functions` | 28,742 | 618 | Fits |
| `lines_from_functions_polar` | 29,616 | 630 | Fits |
| `scatter_and_histogram_from_distribution` | 44,868 | 1,718 | Exceeds 32,256 |

The two oversized sketches compile and link far enough to report section sizes, then fail the board's flash-size check. Their current settings need more flash or reduced rendering complexity. These limits are separate from C++ language compatibility.

Static SRAM means `.data + .bss`; it excludes runtime stack, heap, spline construction and any driver-owned framebuffer. Triangle scratch is used per clipping call after subdivision reaches a leaf. These compiler results do not establish physical display timing or guarantee runtime SRAM headroom. See [PRECISION.md](../../PRECISION.md#verification) for the final matched float/FP16 storage comparison.
