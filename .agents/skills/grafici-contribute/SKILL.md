---
name: grafici-contribute
description: Change or review Grafici-GFX internals, examples or documentation while preserving its normalized interfaces, Arduino resource constraints and repository conventions.
---

# Contribute to Grafici-GFX

Resolve repository paths from this file: the library root is `../../..`. Read the relevant sections of [CONTRIBUTE.md](../../../CONTRIBUTE.md) before changing behavior. Its architecture diagrams, boundary contracts and documentation guidelines are the reference; check the current implementation when they disagree.

## Choose the owning module

| Behavior | Starting point, relative to the library root |
| --- | --- |
| Public overloads, palette selection, axis order | `src/Grafici.h` |
| Raw values, normalized samples, source metadata | `src/Range.h`, `src/data/` |
| Sample traversal and plot geometry | `src/plotter/` |
| Projection and placement | `src/display/Window.h`, `src/display/PolarWindow.h` |
| Subdivision, clipping and pixel conversion | `src/display/DisplayDriver.h`, `src/display/Clipping.h` |
| Color conversion and palettes | `src/color/` |

Keep sources independent of plot styles and display resolution. Plotters consume source interfaces and emit normalized geometry. Windows project float coordinates; the driver clips projected geometry before converting to signed pixels. Clamping each projected vertex would break intersections at the screen edge.

Normalization is an interface, not a storage restriction. Raw data, slopes and intermediate geometry can be signed or exceed one. The current API is float-backed; fixed-point or half-precision storage is not an existing library switch.

## Preserve the contracts

- Arrays, views, interpolation knots and selected palettes are borrowed. Keep their owners alive; name x/y views before storing an interpolator that borrows them. Indexed reads should be repeatable. Bounds, spline coefficients and histogram counts are not automatically refreshed after input changes.
- Use the existing `invalid()` factories and inspect `valid()` before consuming a sample. Missing data must leave the appropriate gaps; zero and constant valid ranges remain legitimate data. Consult the contract table for empty sources, endpoint inclusion and mixed source lengths.
- Retain C++11 support and the default function-pointer callback path. `GRAFICI_USE_STD_FUNCTION` is opt-in, depends on core support and must agree across translation units.

Keep diffs narrow, including existing line endings and formatting. Do not reorganize nearby code to accompany a small fix.

## Account for small boards

Distinguish retained payload, construction workspace and drawing stack. Use the memory formulas in CONTRIBUTE.md rather than treating on-demand sources as free. Explicit ranges avoid discovery scans; repeated source reads, recursive subdivision and display transfers still cost time. Line subdivision splits in two, while filled-triangle subdivision splits in four, so filled plots can increase drawing work much faster. Options contain Arduino `String`, and optional callbacks may allocate.

Prefer bounded storage appropriate to the task. A full framebuffer, cache or numeric-format redesign needs an explicit resource tradeoff; do not add one to all sources for a single feature. Compile with the target board's toolchain and report flash/global SRAM separately from measured peak SRAM and display timing.

## Verify and document the change

Keep host tests and generated images in Grafici-Test. Locate its checkout and available runners; do not assume a temporary path, branch, or a `tests/run_checks.py` that may be absent from that revision. Test behavior at the changed boundary: empty/invalid inputs and endpoints for sources, emitted geometry and gaps for plotters, screen intersections for projections. A host sanitizer pass complements target compilation; neither proves hardware timing or peak memory use.

For documentation, follow CONTRIBUTE.md's walkthrough style: purpose, a small public API example, then visible or numeric output. Reuse interesting functions such as beats or chirps. Keep the README broad and put implementation detail in CONTRIBUTE.md. Preserve Mermaid diagrams and `grafici-example` markers when editing their subjects.

All plot pictures come from actual Grafici-Test rendering. When an illustrated example changes, use that repository's `grafici-render` skill, inspect the regenerated images, and reference a published image commit in Markdown. Updating documentation alone does not require regenerating unchanged plots. Publishing images or updating the wiki follows the user's requested scope.
