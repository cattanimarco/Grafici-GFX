# Boundary and invalid-data contracts

These contracts apply to float and Float16 sources. They add no per-sample flag or buffer. `DataNorm` still stores one scalar and two range bounds: 12 bytes for float and 6 for Float16. The scalar type itself remains signed floating point and can represent values outside `[0,1]`.

| Boundary | Contract |
| --- | --- |
| `Range<T>` | Finite, ordered bounds (`low <= high`) are valid. A constant range is valid, normalizes every finite value to zero, and maps every finite normalized input to its single value. |
| Reversed ranges | Invalid until explicitly sorted. `contains()` returns false. Invalid/non-finite mapping inputs return zero as a deterministic fallback; query `valid()` before using that fallback as data. `norm_to_value()` still clamps finite normalized inputs at 0 and 1. |
| Range accumulation | Start with `Range<T>::invalid()`. `update()` initializes an invalid accumulator from the first finite value and ignores NaN/infinity. `delta()` returns the computation type, so an FP16 span need not fit FP16 storage. |
| `DataNormT` | Default construction and `INVALID_DATA_NORM` represent missing data. `valid()` distinguishes missing data from a legitimate zero or constant range. Raw NaN/infinity, values overflowing the selected storage format, and invalid supplied ranges produce missing data. Finite raw values still clip to an explicit valid range. |
| Source metadata | `DataSourceNormT::valid()` means nonempty with valid range metadata; individual samples can still be missing. Arrays/functions discover bounds from representable finite values. Empty/all-missing inferred sources have invalid ranges. Null array pointers and null function callbacks expose size zero. Explicit range metadata can remain valid on an empty source; its size still reports zero. |
| `DataLinearT` | Zero outputs do not evaluate `size-1`. Inferred bounds sort finite endpoints, so negative slopes are supported. An unrepresentable inferred endpoint produces an empty source. |
| Interpolators/splines | Borrowed sources must remain stable and outlive the interpolator. At least two finite, strictly increasing x knots are required; y may be constant or decrease. Invalid knots produce size zero. `M>=2` includes normalized endpoints; `M=1` emits the first knot. A sample outside the supplied knot coverage is missing. Spline solver failure or non-finite coefficients produce size zero; non-finite/unrepresentable evaluations are missing. Autoscaling measures emitted samples, not continuous extrema between them. |
| Histograms | `BINS` must be positive at compile time. Missing input samples do not contribute to counts or the normalized denominator. An empty histogram retains its bins, all containing valid zero counts/frequencies. Zero class count or `class_id >= num_classes` produces size zero. Group coordinates use floating-point computation before narrowing, avoiding integer-product overflow. |
| Windows | Finite, ordered boundaries are valid, including collapsed ranges. Zero slice counts, out-of-range slice indices and invalid subranges produce an invalid window. `valid()` reports this state; projection of invalid input/window metadata produces non-finite coordinates, and drawing rejects invalid windows. Polar subwindows retain their parent window. |
| Plotters | Missing samples create gaps: lines/areas omit segments touching a missing coordinate or color, bars omit that sample, and scatter omits that marker. Dots do not require a radius; other markers also require a valid, available radius. Invalid/non-finite bar thickness produces no bars. No unbounded cache or validity buffer is created. |
| Display boundary | Project logical geometry without per-vertex clamping. Intersect projected lines/triangles with the physical display rectangle in the computation type, reject non-finite projections, then convert to signed `int16_t` pixels. Zero/negative display dimensions draw nothing. Clipping uses the physical display rectangle; markers can extend beyond a subwindow if still on display. |
| Palettes | Array/generated maps return black for invalid normalized input. A zero-size generated palette reports invalid and returns black. Cosine-generated channels clamp to `[0,255]` before integer conversion. Linear color blends round to nearest, with ties upward. |

For example:

```cpp
DataNorm missing;
DataNorm zero(0, {0, 0});
// !missing.valid(), zero.valid(), zero.norm() == 0

const float readings[] = {NAN, 10, 20};
DataArray<float> source(readings, 3);
// Inferred range [10,20]; source[0] is missing. Plotters leave a gap.
```

Invalidity is encoded by reversed range bounds (`{1,0}`), so code must use `valid()` rather than inspect an old zero sentinel. Calling `norm()` on missing data returns zero for compatibility with arithmetic callers; that zero does not make the sample valid. Converting adapters preserve invalidity across precision families.

FP16's finite range and quantization still apply to raw counts, range metadata and coefficients. Use the float pipeline when those values are not representable. Histograms with FP16 samples and a float interface can retain large integer counters without narrowing raw count metadata. Spline construction retains its bounded heap workspace; these contracts do not remove it.

Pixel conversion preserves truncation toward zero after clipping to `[0,1]`; integer pixel endpoints remain within `[0,width-1]` and `[0,height-1]`. Subdivision still happens before projection, preserving the existing polar/custom-window approximation. A clipped triangle can become a convex polygon with at most seven vertices; two seven-point buffers use 112 bytes of coordinate payload with FP32 computation, plus locals and backend call stack. This is bounded scratch storage, with no heap allocation or framebuffer.

`plot.clear_screen()` uses the native GFX fill. Passing an explicit window retains projected rectangle rendering, including clipping and any requested subdivision. The native default avoids retaining the triangle renderer in simple line sketches.
