# Sorting & Batching

The order you draw in matters. Draw opaque objects front-to-back and the depth buffer rejects hidden pixels early; draw transparent objects back-to-front and they blend correctly. On top of that, grouping draws that share a shader or material cuts down on expensive state changes, and once like objects sit next to each other, the assembler can collapse them into a single instanced draw. This page covers passes, sort order, and the batching that ties them together.

![An unsorted draw list of mixed materials is sorted by material key into contiguous batches, so fewer state changes means fewer draw calls](./../../docs-assets/php-glfw/user_guide/rendering/sort_batch.jpg){ width="100%" }

## Passes

Every instance belongs to a render pass, chosen with the `pass` argument to `submit()`:

```php
use GL\Rendering\DrawCallAssembler;

$assembler->submit($glassHandle, $transform, materialId: 5, pass: DrawCallAssembler::PASS_TRANSPARENT);
```

The available passes are `PASS_OPAQUE`, `PASS_TRANSPARENT`, `PASS_DEPTH`, and `PASS_USER`. Passes are kept separate in the final draw order, and each pass carries the sorting behavior that suits it. Most importantly, the **transparent pass is automatically sorted back-to-front** so your blending comes out right, without you asking.

## Sort Mode

For the opaque pass, you choose the ordering with `setSortMode`:

```php
// draw nearest first, so the depth test rejects hidden fragments early
$assembler->setSortMode(DrawCallAssembler::SORT_FRONT_TO_BACK);

// draw farthest first (rarely needed for opaque; automatic for transparent)
$assembler->setSortMode(DrawCallAssembler::SORT_BACK_TO_FRONT);

// leave submission order untouched
$assembler->setSortMode(DrawCallAssembler::SORT_NONE);
```

Under the hood the assembler builds a packed 64-bit sort key per instance, folding pass, program, material, mesh, and depth into one integer, and sorts with an adaptive algorithm (radix, quicksort, or insertion sort depending on batch size). The upshot for you: instances that share state end up adjacent, which is exactly what makes batching possible. If you ever need to override the computed order for a specific instance, nudge it with the `sortBias` argument to `submit()`.

```mermaid
graph LR
  K["64-bit sort key<br/>pass | program | material | mesh | depth"] --> S[stable sort];
  S --> A[instances that share state<br/>land next to each other];
  A --> C[collapsed into one<br/>instanced draw call];
```

## Instanced Batching

Here's where all that sorting pays off. When many instances share the same mesh, material, pass, and shader program, there's no reason to issue a separate draw call for each; they can be drawn together in a single *instanced* call. The assembler does this automatically: after sorting, it collapses adjacent instances that share those attributes into one batched command.

![PHP-GLFW DrawCallAssembler batching a field of ships sharing a small set of materials](./../../docs-assets/php-glfw/user_guide/rendering/batching_colors.jpg){ width="100%" }

Every ship above shares one of only a handful of materials, so the thousands of instances collapse into a handful of instanced draw calls, one per material.

Batching is on by default. You can toggle it explicitly:

```php
$assembler->setAutoInstancing(true);  // the default
```

This is the difference between 10,000 draw calls and a dozen. In the [command buffer](/user-guide/rendering/render-paths.html#driving-the-draws-yourself-build), a batched draw shows an instance count greater than 1 (field 6), and its instances sit contiguously in the transform buffer starting at the instance offset (field 5).

For batching to render, your shader must read the per-instance transform as a vertex attribute, and you must wire that up once with `bindTransformBuffer()`. See [Render Paths](/user-guide/rendering/render-paths.html) and, for sending extra per-instance data, [Per-Instance Payloads](/user-guide/rendering/payload-attributes.html).

If you ever need identical instances to stay as separate draw calls, for instance to apply per-draw state that instancing can't express, submit them with `FLAG_DISABLE_INSTANCING`:

```php
$assembler->submit(
    meshHandle: $shipHandle,
    transform: $transform,
    materialId: 0,
    flags: DrawCallAssembler::FLAG_DISABLE_INSTANCING,
);
```
