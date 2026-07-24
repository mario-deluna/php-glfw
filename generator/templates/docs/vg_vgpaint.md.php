# VGPaint

A `VGPaint` describes how a shape is filled or stroked with something richer than a flat color:
a gradient or an image. It is an opaque handle with no methods or properties of its own. You obtain
one from a factory and then hand it to the context to use it.

```php
namespace GL\VectorGraphics
{
    class VGPaint {}
}
```

You create a `VGPaint` from one of:

- [`VGContext::linearGradient`](../../API/VectorGraphics/VGContext.md#lineargradient)
- [`VGContext::boxGradient`](../../API/VectorGraphics/VGContext.md#boxgradient)
- [`VGContext::radialGradient`](../../API/VectorGraphics/VGContext.md#radialgradient)
- [`VGImage::makePaint`](../../API/VectorGraphics/VGImage.md#makepaint) /
  [`makePaintCentered`](../../API/VectorGraphics/VGImage.md#makepaintcentered)

And you use it with:

- [`VGContext::fillPaint`](../../API/VectorGraphics/VGContext.md#fillpaint)
- [`VGContext::strokePaint`](../../API/VectorGraphics/VGContext.md#strokepaint)

!!! tip "Looking for a walkthrough?"
    The [Gradients](../../user-guide/vector-graphics/gradients.md) and
    [Images](../../user-guide/vector-graphics/images.md) user guides show paints in action.

## Usage

```php
use GL\VectorGraphics\VGColor;

// build a paint from a gradient
$paint = $vg->linearGradient(0, 0, 0, 200, VGColor::red(), VGColor::blue());

// use it as the fill for the next shape
$vg->beginPath();
$vg->rect(0, 0, 200, 200);
$vg->fillPaint($paint);
$vg->fill();
```
